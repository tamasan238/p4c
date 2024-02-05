	.text
	.file	"action_fwd_ubpf.c"
	.globl	entry                           # -- Begin function entry
	.p2align	3
	.type	entry,@function
entry:                                  # @entry
# %bb.0:
	r7 = r2
	r6 = r1
	call 9
	r1 = 2
	r2 = *(u32 *)(r7 + 0)
	if r2 == 1 goto LBB0_3
# %bb.1:
	if r2 != 2 goto LBB0_4
# %bb.2:
	r1 = 1
LBB0_3:
	r2 = 3
	*(u32 *)(r7 + 8) = r2
	*(u32 *)(r7 + 12) = r1
LBB0_4:
	r1 = r6
	r2 = 0
	call 8
	r0 = 1
	exit
.Lfunc_end0:
	.size	entry, .Lfunc_end0-entry
                                        # -- End function
	.addrsig
