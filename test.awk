# count comes from -v arg
# if count is less than zero -> infinite loop

BEGIN {
	if (length(count) == 0) {
		print "Count is empty!"
		print "Use -v count='Number'"
		exit
	}

	if (!(match(count, /[0-9]/))) {
		print "Count is not a numerical value!"
		exit
	}

	ORS = " "
	srand();
	if (count < 0) {
		print "WARNING!!! Entering Infinite Loop!\n\n"
		system("sleep 3")
		for (;;) {
			test_var = int(rand() * 2)
			print test_var;
		}
	}


	for (i = 1; i <= count; i++) {
		num1 = int(rand() * 90 + 10);    # sadece iki basamakli sayilar 10 - 99
		print num1;
	}

	ORS = "\n"
	num1 = int(rand() * 90 + 10);    # sadece iki basamakli sayilar 10 - 99
	print num1;
}

