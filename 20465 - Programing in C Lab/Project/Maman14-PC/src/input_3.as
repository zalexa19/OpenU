.extern LABEL1
.extern LABEL2
.extern LABEL5
	add #1,r5
	not LABEL1
	cmp STR,STR2
STR: .string "string1"
	clr r4
STR2: .string "string2"
	stop

