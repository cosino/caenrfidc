caenrfidc
=========

This package implements the client side of CAENRFID protocol in C and allow
the user to supply some commands to the RFID UHF reader.

This code can be used to get access to the CAENRFID RFID UHF readers,
expecially for the Cosino Mega 2560 - UHF RFID KIT
(http://www.cosino.io/product/cosino-mega-2560-uhf-rfid-kit).

<em>Note that the following code is the unofficial version of the CAENRFID's code so
don't waste the CAENRFID's guys on questions about what you're reading here!</em>

<b>Note</b>: this program is still a beta version! So don't use it for production!!


Quick usage
-----------

Available commands are those reported by the <code>help</code> command as follow:

    help
    ok: commands list:
    ok: 	exit 
    ok: 	info 
    ok: 	help [<command>]
    ok: 	radio open (<comm_proto> [options] | close <id>)
    ok: 	channel <id> (get | set <chan>)
    ok: 	fw_release <id>
    ok: 	inventory <id> <src>
    ok: 	modulation <id> (get | set <proto>)
    ok: 	power <id> (get | set <pow>)
    ok: 	protocol <id> (get | set <proto>)
    ok: 	regulation <id> (get | set <reg>)
    ok: 	readpoint <id> <name> (add <ant> | rm <ant> | chk <ant>)
    ok: 	read <id> <EPC> RES|EPC|TID|USR <offset> <#bytes> [<passwd>]

Command <code>exit</code> is used to end the program, while command <code>info</code> displays some
program's information:

    info
    ok: caenrfidc - version 0.10.0

The <code>help</code> command can display the above output but it can be used to show
specific commands help also:

    help inventory
    ok: inventory <id> <src>

The command <code>radio</code> is used to open a connection with a specific RFID reader,
so for instance to get connected with the RFID UHF reader of the Cosino Mega
2560 - UHF RFID KIT we can use the command:

    radio open rs232 /dev/ttyS2 
    ok: id=0

The <code>id=0</code> means that current radio ID is 0; this value must be used in all
RFID action commands to address our reader. So, for instance, to get the
current reader's firmware version we should use the command:

    fw_release 0
    ok: rel=4.1.0

Now we can get the current power level by using the <code>power</code> command:

    power 0 get
    ok: pow=446

In the end, to do an inventory we can use the homonymous command:

    inventory 0 Source_0
    ok: size=2
    ok: epc=e280113020002431ddbc00ab src=Source_0 rp=Ant0 type=3 rssi=0
    ok: epc=e280113020002491ddbc00ab src=Source_0 rp=Ant0 type=3 rssi=0

Enjoy! :-)
