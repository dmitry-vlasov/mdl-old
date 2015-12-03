/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Indent.cpp                                    */
/* Description:     indent                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_INDENT_CPP_
#define NSTD_LEXER_INDENT_CPP_

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Indent :: Indent(const Index_ tabs, const Index_ spaces) :
	tabs_ (tabs),
	spaces_ (spaces) {
	}
	inline Indent :: Indent (const Indent& indent) :
	tabs_ (indent.tabs_),
	spaces_ (indent.spaces_) {
	}

	inline bool
	Indent :: operator == (const Indent& indent) const
	{
		return
			(spaces_ == indent.spaces_) &&
			(tabs_ == indent.tabs_);
	}
	inline bool
	Indent :: operator != (const Indent& indent) const {
		return !(operator == (indent));
	}
	inline void
	Indent :: operator = (const Indent& indent)
	{
		spaces_ = indent.spaces_;
		tabs_ = indent.tabs_;
	}

	inline void
	Indent :: incSpaces() {
		spaces_ ++;
	}
	inline void
	Indent :: incTabs() {
		tabs_ ++;
	}
	inline void
	Indent :: newLine() {
		spaces_ = 0;
		tabs_ = 0;
	}

	inline bool
	Indent :: isEmpty() const {
		return (spaces_ == 0) && (tabs_ == 0);
	}

	inline void
	Indent :: clear() {
		spaces_ = 0;
		tabs_ = 0;
	}

	template<class A>
	void
	Indent :: print (String<A>& string) const
	{
		for (Index_ i = 0; i < tabs_; i++) {
			string << manipulator :: tab;
		}
		for (Index_ i = 0; i < spaces_; i++) {
			string << manipulator :: space;
		}
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// nstd :: Object implementation
	void
	Indent :: commitSuicide() {
		delete this;
	}
	Size_t
	Indent :: getVolume() const {
		return 0;
	}
	Size_t
	Indent :: getSizeOf() const {
		return sizeof (Indent);
	}
	void
	Indent :: show (String<>& string) const
	{
		string << "tabs:" << space << tabs_ << "," << space;
		string << "spaces:" << space << spaces_ << "." << endLine;
	}

	/****************************
	 *		Operators
	 ****************************/

	template<class A>
	String<A>&
	operator << (String<A>& string, const Indent& indent)
	{
		indent.print (string);
		return string;
	}
}
}

#endif /* NSTD_LEXER_INDENT_CPP_ */
