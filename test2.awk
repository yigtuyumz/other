# count comes from -v arg
# if count < 0 -> infinite loop

function bits2str(bits,        data, mask)
{
	if (bits == 0)
		return "0"

	mask = 1;
	for (; bits != 0; bits = rshift(bits, 1)) {
		data = (and(bits, mask) ? "1" : "0") data
	}

	while ((length(data) % 8) != 0) {
		data = "0" data
	}
	return (data);
}

BEGIN {
	if (length(count) == 0) {
		printf("Count is empty!\n");
		printf("Use -v count='Number'\n");
		exit;
	}

	if (!(match(count, /[0-9]/))) {
		printf("Count is not a numerical value!\n");
		exit;
	}

	# Output Record Seperator
	ORS = " ";
	srand();

	if (count < 0) {
		printf("WARNING!!! Entering Infinite Loop!\n");
		system("sleep 0")
		for (;;) {
			num = int(rand() * 25) + 65;
			printf("%08d\t%c\n", bits2str(num), num);
		}
	}

	else {
		for (i = 1; i <= count; i++) {
			num = int(rand() * 25) + 65;
			printf("%08d\t%c\n", bits2str(num), num);
		}
		ORS = "\n";
		# sadece iki basamakli sayilar 10 - 99
		# printf("%d ", int(rand() * 90 + 10));
	}
}

