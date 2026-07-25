#pragma once

#include <Syringe.h>

// In this file: Alternatives to CTRL + H...

// macros DCoder uses and pd dislikes :)

#define GET(clsname, var, reg) \
	clsname var = R->reg<clsname>();

// it's really not a good idea to GET_STACK(not_a_pointer)
// no, really
#define LEA_STACK(clsname, var, offset) \
	clsname var = R->lea_Stack<clsname>(offset);

#define REF_STACK(clsname, var, offset) \
	clsname& var = R->ref_Stack<clsname>(offset);

#define GET_STACK(clsname, var, offset) \
	clsname var = R->Stack<clsname>(offset);

#define GET_BASE(clsname, var, offset) \
	clsname var = R->Base<clsname>(offset);

#define STACK_OFFSET(cur_offset, wanted_offset) \
		(cur_offset + wanted_offset)

// NOTE (Antares): upstream renamed STACK_OFFS to STACK_OFFSET *and flipped the
// sign* of the second operand. Ares writes all 68 of its stack reads in the old
// form -- STACK_OFFS(0xE0, 0xB4) means "the frame was 0xE0 deep at hook entry and
// the variable sits at [esp+0xB4]", which is how the offsets were read off IDA and
// how the recon notes record them. Mechanically renaming them would require
// negating 68 hand-derived literals, and a slip there produces a wrong stack read:
// a runtime crash or silent garbage that no gate in this tree can see. So the old
// name keeps the old meaning, and upstream's STACK_OFFSET keeps its own.
#define STACK_OFFS(cur_offset, wanted_offset) \
		(cur_offset - wanted_offset)


// swizzle shorthand
#define SWIZZLE(var) \
	SwizzleManagerClass::Instance.Swizzle((void **)&var)


#include <cmath>
// float cmp
#define CLOSE_ENOUGH(x, y) \
	(fabs(x - y) < 0.001)

#define LESS_EQUAL(x, y) \
	((x - y) <= 0.001)
