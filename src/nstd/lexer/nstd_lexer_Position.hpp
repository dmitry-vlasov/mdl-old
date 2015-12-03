/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Position.hpp                                  */
/* Description:     position in input stream                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_POSITION_HPP_
#define NSTD_LEXER_POSITION_HPP_

namespace nstd {
namespace lexer {

class Position : public Object {
public :
	typedef U_int16_t Column_;
	typedef U_int32_t Line_;
	typedef U_int32_t Index_;

	Position ();
	Position (const Position&);
	Position (const Line_, const Column_);

	Line_ getLine() const;
	Column_ getColumn() const;
	Index_ getIndex() const;

	void incColumn();
	void incLine();
	void incIndex();

	void clear();
	void start();

	void operator = (const Position&);
	bool operator == (const Position&) const;
	bool operator != (const Position&) const;
	bool operator < (const Position&)  const;
	bool operator <= (const Position&) const;
	bool operator > (const Position&)  const;
	bool operator >= (const Position&) const;

	bool precedes (const Line_, const Column_) const;
	bool follows (const Line_, const Column_) const;

	bool isUndefined() const;
	void setup (const Line_, const Column_);

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	Column_ column_;
	Line_ line_;
};

}
}

#endif /*NSTD_LEXER_POSITION_HPP_*/
