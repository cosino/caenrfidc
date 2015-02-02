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
	print "#include \"commands.h\"\n";
	print "struct command_s commands_list[] = {";
}

# Skip comments
/^[[:space:]]*#.*$/ {
	next
}

# Skip blank lines
/^[[:space:]]*$/ {
	next
}

/.*/ {
	name = trim($1);
	usage = trim($2);
	num++;

	printf "\tcommand(%s,\n", name;
	if (length(usage))
		printf "\t\t\"%s\"),\n", usage;
	else
		printf "\t\tNULL),\n";
}

END {
	print "\t{ },\t/* array terminator */\n};";
}
