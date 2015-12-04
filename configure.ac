#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.64)
AC_INIT(mdl, 0.8.9-110, vlasov at academ dot org)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

AM_LDFLAGS='-static'
AX_PTHREAD
CXXFLAGS='-pthread'

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

# Checks for header files.
AC_CHECK_HEADERS #([limits.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gettimeofday mkdir pow strchr strcspn strstr])

AC_CONFIG_FILES([
Makefile
	
math/Makefile
scripts/Makefile
metamath/Makefile

src/Makefile

src/nstd/Makefile
	src/nstd/config/Makefile
		src/nstd/config/option/Makefile
	src/nstd/container/Makefile
		src/nstd/container/continual/Makefile
		src/nstd/container/discrete/Makefile
		src/nstd/container/storage/Makefile
	src/nstd/equation/Makefile
	src/nstd/interpolation/Makefile
	src/nstd/lexer/Makefile
	src/nstd/map/Makefile
	src/nstd/memory/Makefile
		src/nstd/memory/allocator/Makefile
		src/nstd/memory/exception/Makefile
		src/nstd/memory/storage/Makefile
		src/nstd/memory/unit/Makefile
	src/nstd/misc/Makefile
	src/nstd/sampler/Makefile
	src/nstd/type/Makefile
		src/nstd/type/constant/Makefile
		src/nstd/type/list/Makefile
		src/nstd/type/traits/Makefile
			src/nstd/type/traits/indicator/Makefile
		src/nstd/type/undefined/Makefile
	src/nstd/system/Makefile

src/mm/Makefile
	src/mm/ast/Makefile
		src/mm/ast/source/Makefile
			src/mm/ast/source/hypothesis/Makefile
			src/mm/ast/source/reference/Makefile
		src/mm/ast/target/Makefile
			src/mm/ast/target/assertion/Makefile
			src/mm/ast/target/header/Makefile
				src/mm/ast/target/header/proposition/Makefile
				src/mm/ast/target/header/term/Makefile
			src/mm/ast/target/step/Makefile
	src/mm/auxiliary/Makefile
	src/mm/cut/Makefile
		src/mm/cut/auxiliary/Makefile
		src/mm/cut/interface/Makefile
		src/mm/cut/lexer/Makefile
		src/mm/cut/parser/Makefile
		src/mm/cut/source/Makefile
	src/mm/expression/Makefile
	src/mm/interface/Makefile
		src/mm/interface/object/Makefile
		src/mm/interface/source/Makefile
		src/mm/interface/stack/Makefile
		src/mm/interface/target/Makefile
	src/mm/lexer/Makefile
	src/mm/math/Makefile
	src/mm/parser/Makefile
		src/mm/parser/block/Makefile
	src/mm/types/Makefile

src/smm/Makefile
	src/smm/auxiliary/Makefile
	src/smm/expression/Makefile
	src/smm/interface/Makefile
		src/smm/interface/object/Makefile
		src/smm/interface/source/Makefile
	src/smm/lexer/Makefile
	src/smm/math/Makefile
	src/smm/parser/Makefile
	src/smm/source/Makefile
	src/smm/types/Makefile
	
src/mdl/Makefile
	src/mdl/auxiliary/Makefile
		src/mdl/auxiliary/config/Makefile
		src/mdl/auxiliary/parameter/Makefile
		src/mdl/auxiliary/pool/Makefile
		src/mdl/auxiliary/statistics/Makefile
	src/mdl/console/Makefile
	src/mdl/expression/Makefile
		src/mdl/expression/build/Makefile
		src/mdl/expression/direction/Makefile
		src/mdl/expression/iterator/Makefile
			src/mdl/expression/iterator/constant/Makefile
			src/mdl/expression/iterator/modifier/Makefile
		src/mdl/expression/node/Makefile
			src/mdl/expression/node/container/Makefile
			src/mdl/expression/node/prototype/Makefile
			src/mdl/expression/node/terms/Makefile
			src/mdl/expression/node/valued/Makefile
		src/mdl/expression/parse/Makefile
		src/mdl/expression/simify/Makefile
		src/mdl/expression/unify/Makefile
			src/mdl/expression/unify/exp/Makefile
			src/mdl/expression/unify/fact/Makefile
			src/mdl/expression/unify/sub/Makefile
				src/mdl/expression/unify/sub/prod/Makefile
				src/mdl/expression/unify/sub/tree/Makefile
	src/mdl/form/Makefile
		src/mdl/form/block/Makefile
		src/mdl/form/evaluation/Makefile
			src/mdl/form/evaluation/function/Makefile
			src/mdl/form/evaluation/lexp/Makefile
			src/mdl/form/evaluation/term/Makefile
		src/mdl/form/header/Makefile
			src/mdl/form/header/statement/Makefile
			src/mdl/form/header/term/Makefile
		src/mdl/form/proof/Makefile
			src/mdl/form/proof/node/Makefile
			src/mdl/form/proof/notation/Makefile
			src/mdl/form/proof/scope/Makefile
			src/mdl/form/proof/step/Makefile
	src/mdl/interface/Makefile
		src/mdl/interface/block/Makefile
		src/mdl/interface/evaluation/Makefile
		src/mdl/interface/header/Makefile
			src/mdl/interface/header/statement/Makefile
			src/mdl/interface/header/term/Makefile
		src/mdl/interface/object/Makefile
		src/mdl/interface/proof/Makefile
	src/mdl/lexer/Makefile
	src/mdl/math/Makefile
	src/mdl/parser/Makefile
		src/mdl/parser/block/Makefile
		src/mdl/parser/evaluation/Makefile
		src/mdl/parser/header/Makefile
		src/mdl/parser/proof/Makefile
	src/mdl/prover/Makefile
		src/mdl/prover/data/Makefile
		src/mdl/prover/evidence/Makefile
		src/mdl/prover/interface/Makefile
		src/mdl/prover/node/Makefile
		src/mdl/prover/proof/Makefile
		src/mdl/prover/tree/Makefile
			src/mdl/prover/tree/down/Makefile
			src/mdl/prover/tree/up/Makefile
	src/mdl/refactor/Makefile
		src/mdl/refactor/redundant/Makefile
	src/mdl/study/Makefile
		src/mdl/study/benchmark/Makefile
		src/mdl/study/lexp/Makefile
		src/mdl/study/teach/Makefile
		src/mdl/study/tune/Makefile
	src/mdl/types/Makefile
	
src/del/Makefile
	src/del/auxiliary/Makefile
	src/del/interface/Makefile
		src/del/interface/model/Makefile
			src/del/interface/model/queue/Makefile
	src/del/lexer/Makefile
	src/del/math/Makefile
	src/del/model/Makefile
		src/del/model/interpretation/Makefile
		src/del/model/node/Makefile
			src/del/model/node/negative/Makefile
			src/del/model/node/positive/Makefile
		src/del/model/queue/Makefile
			src/del/model/queue/domain/Makefile
			src/del/model/queue/impl/Makefile
			src/del/model/queue/range/Makefile
	src/del/owl/Makefile
		src/del/owl/func/Makefile
			src/del/owl/func/lexer/Makefile
			src/del/owl/func/parser/Makefile
			src/del/owl/func/source/Makefile
		src/del/owl/man/Makefile
			src/del/owl/man/lexer/Makefile
			src/del/owl/man/parser/Makefile
			src/del/owl/man/source/Makefile
	src/del/parser/Makefile
	src/del/source/Makefile
		src/del/source/formula/Makefile
			src/del/source/formula/equiv/Makefile
			src/del/source/formula/subset/Makefile
				src/del/source/formula/subset/normal/Makefile
		src/del/source/term/Makefile
	src/del/types/Makefile
])
AC_OUTPUT
