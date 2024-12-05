/* if you install mysql as a global package, consider to change path. */
const mysql = require('mysql');

const __DEBUG__ = 1;

class DbConnection {
  constructor(options) {
    this.options = options;
    this.connection = null;
  }

  connect(host, user, password, database = null, port = 3306) {
    this.connection = mysql.createConnection(Object.assign({},
      this.options,
      {
        host: host,
        user: user,
        password: password,
        database: database,
        port: port,
      }
    ));
    return (new Promise((resolve, reject) => {
      this.connection.connect((error) => {
        if (error) {
          this.connection = null;
          reject(error);

        } else {
          if (__DEBUG__) {
            console.log("MySQL Connection successful. thread: "
              + this.connection.threadId);
          }
          resolve();
        }
      });
    }));
  }

  async send_query(sqlStmt, values = []) {
    if (!this.connection) {
      throw new Error("Could not connect to the database.");
    }
    return (new Promise((resolve, reject) => {
      this.connection.query(sqlStmt, values, (error, response) => {
        if (error) {
          reject(error);
        } else {
          resolve(response);
        }
      });
    }));
  }

  async end() {
    if (this.connection) {
      return (new Promise((resolve, reject) => {
        this.connection.end((error) =>{
          if (error) {
            reject(error);
          } else {
            if (__DEBUG__) {
              console.log('thread: '
                + this.connection.threadId
                + ' ended successfuly.');
            }
            this.connection = null;
            resolve();
          }
        });
      }));
    }
  }
};

const DBConnection = new DbConnection({multipleStatements: true});

/* if you get ER_NOT_SUPPORTED_AUTH_MODE, use IP addr in host field. */
const host = 'localhost';
const userName = 'root';
const passwd = '********';

(async () => {
  await DBConnection.connect(host, userName, passwd);
  try {
    let queryResult = await DBConnection.send_query('SHOW DATABASES;', []);
    if (__DEBUG__) {
      console.log(queryResult);
    }
    await DBConnection.end();
  } catch (error) {
    console.log(error.message);
  }
})();
