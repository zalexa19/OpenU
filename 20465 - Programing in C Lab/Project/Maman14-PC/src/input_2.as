.entry LENGTH
.extern L3
.extern W
LABEL:	cmp r3,r4
		red LABEL
M:	jmp W
STR:	.string "hello world"
		bne r7
		inc L3
END:	stop
LENGTH: .data 6,9,15
K:		.data 22
