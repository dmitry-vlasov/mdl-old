/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Symbol.cpp                                 */
/* Description:     Russell symbol table class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_SYMBOL_CPP_
#define MDL_AUXILIARY_SYMBOL_CPP_

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Symbol :: Symbol (const Size_t nameVectorCapacity) :
	table_ (nameVectorCapacity),
	ascii_ (nameVectorCapacity),
	latex_ (nameVectorCapacity) {
	}
	Symbol :: ~ Symbol() {
	}

	inline value :: Literal
	Symbol :: add
	(
		const String* symbol,
		const String* ascii,
		const String* latex
	)
	{
		ascii_.add (ascii);
		latex_.add (latex);
		return table_.add (*symbol);
	}

	inline const String*
	Symbol :: getAscii (const value :: Literal ind) const {
		return ascii_.getValue (ind);
	}
	inline const String*
	Symbol :: getUnicode (const value :: Literal ind) const {
		return &(table_.get (ind));
	}
	inline const String*
	Symbol :: getLatex (const value :: Literal ind) const {
		return latex_.getValue (ind);
	}

	// nstd :: Symbol implementation
	inline const String&
	Symbol :: get (const value :: Literal value) const {
		return table_.get (value);
	}
	inline value :: Literal
	Symbol :: add (const String& string)
	{
		const value :: Literal result = table_.add (string);
		if (table_.addedNew()) {
			ascii_.add (&table_.get (result));
			latex_.add (NULL);
		}
		return result;
	}
	inline value :: Literal
	Symbol :: add (const char* const string)
	{
		const value :: Literal result = table_.add (string);
		if (table_.addedNew()) {
			ascii_.add (&table_.get (result));
			latex_.add (NULL);
		}
		return result;
	}
	inline value :: Literal
	Symbol :: find (const String& string) const {
		return table_.find (string);
	}
	inline value :: Literal
	Symbol :: find (const char* const string) const {
		return table_.find (string);
	}
	inline bool
	Symbol :: contains (const String& string) const {
		return table_.contains (string);
	}
	inline bool
	Symbol :: contains (const char* const string) const {
		return table_.contains (string);
	}
	void
	Symbol :: dumpLiteral (value :: Literal literal) const {
		table_.dumpName (literal);
	}

	// nstd :: Object implementation
	void
	Symbol :: commitSuicide() {
		delete this;
	}
	Size_t
	Symbol :: getVolume () const
	{
		Size_t result = 0;
		result += table_.getVolume();
		result += ascii_.getVolume();
		result += latex_.getVolume();
		return result;
	}
	Size_t
	Symbol :: getSizeOf () const {
		return sizeof (Symbol);
	}
	void
	Symbol :: show (nstd :: String<>& string) const {
		table_.show (string);
	}
}
}

#endif /*MDL_AUXILIARY_SYMBOL_CPP_*/
