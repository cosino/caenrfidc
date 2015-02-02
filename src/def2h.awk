# Remove leading and trailing spaces chars
function trim(v) {
	sub("^[ \t]*", "", v);
	sub("[ \t]*$", "", v);
	return v;
}

# Main

BEGIN {
	FS = ";";		# set CSV separator
	num = 0;

	print "/* Auto generated file, DON'T EDIT! */";
	print "#include \"client.h\"\n";
}

# Skip comments
/^[:space:]*#.*$/ {
	next
}

# Skip blank lines
/^[:space:]*$/ {
	next
}

/.*/ {
	name = trim($1);
	usage = trim($2);
	num++;

	printf "extern int cmd_%s(struct command_s *cmd, int argc, char *argv[]);\n",
		name;
}
