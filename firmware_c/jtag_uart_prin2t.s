#-----------------------------------------------------------------------------
# This template source file for ELEC 371 Lab 2 experimentation with interrupts
# also serves as the template for all assembly-language-level coding for
# Nios II interrupt-based programs in this course. *DO NOT USE* the approach
# shown in the vendor documentation for the DE0 Basic (or Media) Computer.
# The approach illustrated in this template file is far simpler for learning.
#
# Dr. N. Manjikian, Dept. of Elec. and Comp. Eng., Queen's University
#	
# (revised Sept. 2025 for startup code calling main routine and updated
#  comments/explanations for the code)	
#-----------------------------------------------------------------------------

	.text		# start a code segment (which will also included data)

	.global	_start	# export _start symbol for linker 

#-----------------------------------------------------------------------------
# Define symbols for memory-mapped I/O register addresses and use them in code
#-----------------------------------------------------------------------------
# data register for pushbutton

	.equ	BUTTON, 0x10000050

# mask/edge registers for pushbutton parallel port

	.equ	BUTTON_MASK, 0x10000058
	.equ	BUTTON_EDGE, 0x1000005C

# pattern corresponding to the bit assigned to button1 in the registers above

	.equ	BUTTON1, 0x2
	.equ	U5LED, 0b1111100000

# data register for LED parallel port

	.equ	LEDS, 0x10000010
	
	.equ	TIMER_STATUS, 0x10002000
	.equ	TIMER_CONTROL, 0x10002004
	.equ	TIMER_START_LO, 0x10002008
	.equ	TIMER_START_HI, 0x1000200C

#-----------------------------------------------------------------------------
# Define two branch instructions in specific locations at the start of memory
#-----------------------------------------------------------------------------

	.org	0x0000		# this is the _reset_ address 
_start:
	movia	sp, 0x007FFFFC	# initialize stack pointer
	call	main		# *call* the main() routine
	break			# terminate if there is a return from main()

	# The movia is 2 actual instructions, call is 1 instruction,
	#   and break is 1 instruction. Hence, (2+1+1) * 4 bytes/instruction
	#   is 16 bytes for the code above, or 0x10 in hexadecimal.
	# There is sufficient space without overlap for the code below
	#   that *must* be at the specified address.
	
	.org	0x0020	# this is the _exception/interrupt_ address

	br	isr	# *branch* to start of interrupt service routine 
			#   (rather than placing all of the service code here) 

#-----------------------------------------------------------------------------
# The actual program code (incl. service routine) can be placed immediately
# after the second branch above, or another .org directive could be used
# to place the program code at a desired address (e.g., 0x0080). It does not
# matter because the _start symbol defines where execution begins, and the
# startup code at that location causes execution to reach the code below.
#-----------------------------------------------------------------------------

main:
	subi    sp,sp, 12
    stw		ra,	8(sp)
    stw		r2,	4(sp)
	stw		r3,	0(sp)
	call	Init		# call hw/sw initialization subroutine
	call ToggleUpperLEDs

main_loop:

	movia	r3, COUNT
	ldw		r2, 0(r3)
	addi	r2, r2, 1
	stw		r2, 0(r3)

	br main_loop


    ldw		ra,	8(sp)
    ldw		r2,	4(sp)
	ldw		r3,	0(sp)
	addi	sp,sp, 12
	ret

Init:				

	subi	sp, sp, 8
	stw		r2, 4(sp)
	stw		r3, 0(sp)

	movia	r2, 0xBC20
	movia	r3, TIMER_START_LO
	stwio	r2, 0(r3)

	movia	r2, 0x00BE
	movia	r3, TIMER_START_HI
	stwio	r2, 0(r3)
	

	movi	r2, 2			# body of Init() subroutine
	movia	r3, BUTTON_MASK
	stwio	r2, 0(r3)
	
	movi	r2, 0b111
	movia	r3, TIMER_CONTROL
	stwio	r2, 0(r3)

	movi	r2, 0b11
	wrctl	ienable, r2

	movi	r2, 1
	wrctl	status, r2

	ldw		r3,0(sp)
	ldw		r2,4(sp)
	addi	sp, sp, 8

	ret


ToggleUpperLEDs:
	subi	sp, sp, 12
	stw		r2, 0(sp)
	stw		r3, 4(sp)
	stw		r4, 8(sp)

	movi	r2, U5LED
	movia	r3, LEDS
	ldwio	r4, 0(r3)
	xor		r4, r4, r2
	stwio	r4, 0(r3)

		
	ldw		r2, 0(sp)
	ldw		r3, 4(sp)
	ldw		r4, 8(sp)
	addi	sp, sp, 12
	ret

isr:
	subi	sp, sp, 16
	stw		r2, 12(sp)
	stw		r3, 8 (sp)
	stw		r4, 4 (sp)
	stw		ra, 0 (sp)	# save register values, *except* ea which
						#   must be adjusted for hardware interrupts

	subi	ea, ea, 4	# ea adjustment required for h/w interrupts

	rdctl	r3, ipending #read pending interrupts

PUSHCHECK:

	andi	r2, r3, 0b10 #mask to see if it is pushbuttons
	beq		r2, r0, TIMERCHECK 

	movia	r4, LEDS
	ldwio	r2, 0(r4)
	xori	r2, r2, 1
	stwio	r2, 0(r4)


	movi	r2, BUTTON1 #clear pushbutton interrupt request
	movia	r4, BUTTON_EDGE 
	stwio	r2, 0(r4)

TIMERCHECK:
	andi	r2, r3, 0b1
	beq		r2, r0, NEXT
	movia	r3, TIMER_STATUS
	stwio	r0, 0(r3)
	call ToggleUpperLEDs



NEXT:
	ldw		r2, 12(sp)
	ldw		r3, 8 (sp)
	ldw		r4, 4 (sp)
	ldw		ra, 0 (sp)
	addi	sp, sp, 16# restore register values
	
	eret			# interrupt service routines end _differently_
				#   than subroutines -- execution must return
				#   to point in main program where interrupt
				#   request caused invocation of service routine
	
#-----------------------------------------------------------------------------
# Definitions for program data, usually global variables, but where necessary
# there can also be some variables local to only one subroutine whose values
# must be preserved across calls to that subroutine. Global variables include
# any that are used to convey information between the main program and the
# interrupt code (incl. special subroutines called from interrupt code).	
#-----------------------------------------------------------------------------

	.org	0x1000		# start should be fine for most small programs
				
COUNT:		.word	0


	.end
