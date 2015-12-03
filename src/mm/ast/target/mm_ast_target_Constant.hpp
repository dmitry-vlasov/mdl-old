/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Constant.hpp                               */
/* Description:     mdl constant                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_CONSTANT_HPP_
#define MM_AST_TARGET_CONSTANT_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {

class Constant :
	public object :: Targetive,
	public Scalar<Constant> {
public :
	Constant
	(
		const vector :: Literal* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Constant();

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class auxiliary :: Volume;

	void collectConstants () const;
	bool isMeaningful (const value :: Literal) const;
	void writeConstant (const value :: Literal, String&) const;

	const vector :: Literal* const literals_;

	mutable vector :: Literal constants_;
	const mm :: target :: Comments* const comments_;
	mutable const mm :: target :: Block* block_;

	typedef
		Vector
		<
			const String*,
			storage :: ByValue,
			allocator :: Heap
		>
		Strings_;
	enum {
		INITIAL_STRINGS_CAPACITY = 1024
	};

	static bool staticVolumeCounted_;
	static Strings_* translated_;
};

}
}
}

#endif /* MM_AST_TARGET_CONSTANT_HPP_ */
