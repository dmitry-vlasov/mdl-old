/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Indent.hpp                                    */
/* Description:     indent                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace lexer {

class Indent : public Object {
public :
	typedef U_int16_t Index_;

	Indent (const Index_ tabs = 0, const Index_ spaces = 0);
	Indent (const Indent&);

	bool operator == (const Indent&) const;
	bool operator != (const Indent&) const;
	void operator = (const Indent&);

	void incSpaces();
	void incTabs();
	void newLine();

	bool isEmpty() const;

	void clear();
	template<class A>
	void print (String<A>&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	Index_ tabs_;
	Index_ spaces_;
};

	template<class A>
	String<A>&
	operator << (String<A>&, const Indent&);

}
}


