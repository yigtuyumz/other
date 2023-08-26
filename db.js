const mysql = require('mysql'); 

const __DEBUG__ = 1;

class DbConnection {
	// mysql secenekleri, bir obje olarak disaridan aliniyor.
	constructor(options) {
		this.options = options;
	}

	connect(host, user, password, database = null, port = 3306) {
		this.connection = mysql.createConnection(Object.assign({}, this.options, {
			host: host,
			user: user,
			password: password,
			database: database,		// opsiyonel
			port: port,				// opsiyonel, varsayilan 3306
		}));

		return (new Promise((resolve, reject) => {
			this.connection.connect((error) => {
				if (error) {
					reject();
					throw (error);
				} else {
					if (__DEBUG__) {
						console.log('MySQL baglantisi basarili... thread : ' + this.connection.threadId);
					}
					resolve();
				}
			});
		}));
	}

	async send_query(sqlStmt, values = []) {
		if (!this.connect) {
			throw ('Veritabanina baglanilamadi.');
		}
		return (new Promise((resolve, reject) => {
			this.connection.query(sqlStmt, values, (error, response) => {
				if (error) {
					reject();
					throw(error.message);
				} else {
					resolve(response);
				}
			});
		}));
	}

	async end() {
		if (this.connection) {
			return (new Promise((resolve, reject) => {
				// connection.destroy -> bu fonksiyondan sonra hicbir sey gerceklesmez.
				// bunun olmamasi icin connection.end kullaniyoruz.
				this.connection.end((error) => {
					if (error) {
						reject();
						throw (error);
					} else {
						if (__DEBUG__) {
							console.log('thread : ' + this.connection.threadId + ' basariyla sonlandirildi...');
						}
						resolve();
					}
				});
			}));
		}
	}
}

const DBconnection1 = new DbConnection({multipleStatements: true});


(async () => {

	await DBconnection1.connect('localhost', 'user', 'pass');
	try {
		let lastQuery = await DBconnection1.send_query('-- the query;', []);
		if (__DEBUG__) {
			console.log(lastQuery);
		}
		await DBconnection1.end();
	
	} catch (error) {
		console.log(error);
	}
})();
