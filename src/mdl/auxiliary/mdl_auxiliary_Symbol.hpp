/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Symbol.hpp                                 */
/* Description:     Russell symbol table class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_SYMBOL_HPP_
#define MDL_AUXILIARY_SYMBOL_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/mdl_auxiliary.dpp"

namespace mdl {
namespace auxiliary {

class Symbol :
	public nstd :: Object,
	public Scalar<Symbol> {
private :
	typedef
		nstd :: NameTable<value :: Literal, allocator :: Heap>
		NameTable_;
public :
	Symbol (const Size_t = NameTable_ :: INITIAL_NAME_VECTOR_CAPACITY);
	virtual ~ Symbol();

	value :: Literal add (const String*, const String*, const String*);
	const String* getAscii (const value :: Literal) const;
	const String* getUnicode (const value :: Literal) const;
	const String* getLatex (const value :: Literal) const;

	// nstd :: Table interface
	const String& get (const value :: Literal) const;
	value :: Literal add (const String&);
	value :: Literal add (const char* const);
	value :: Literal find (const String&) const;
	value :: Literal find (const char* const) const;
	bool contains (const String&) const;
	bool contains (const char* const) const;
	void dumpLiteral (value :: Literal) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private:
	typedef
		vector :: Vector
		<
			const String*,
			storage :: ByValue,
			allocator :: Heap
		>
		Vector_;

	NameTable_ table_;
	Vector_ ascii_;
	Vector_ latex_;

	enum {
		INITIAL_SYMBOL_VECTOR_CAPACITY = 512
	};
};

}
}

#endif /*MDL_AUXILIARY_SYMBOL_HPP_*/
