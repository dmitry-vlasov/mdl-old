/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Position.cpp                                  */
/* Description:     position in input stream                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_POSITION_CPP_
#define NSTD_LEXER_POSITION_CPP_

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Position :: Position () :
	column_ (0),
	line_ (0) {
	}
	inline
	Position :: Position (const Position& position) :
	column_ (position.column_),
	line_ (position.line_) {
	}
	inline
	Position :: Position (const Line_ line, const Column_ column) :
	column_ (column),
	line_ (line) {
	}

	inline Position :: Line_
	Position :: getLine() const {
		return line_;
	}
	inline Position :: Column_
	Position :: getColumn() const {
		return column_;
	}
	inline Position :: Index_
	Position :: getIndex() const {
		return Undefined<Index_> :: getValue();
	}

	inline void
	Position :: incColumn() {
		++column_;
	}
	inline void
	Position :: incLine() {
		++ line_;
		column_ = 0;
	}
	inline void
	Position :: incIndex() {
	}

	inline void
	Position :: clear()
	{
		column_ = 0;
		line_ = 0;
	}
	inline void
	Position :: start()
	{
		column_ = 0;
		line_ = 1;
	}


	inline void
	Position :: operator = (const Position& position)
	{
		column_ = position.column_;
		line_ = position.line_;
	}
	inline bool
	Position :: operator == (const Position& position) const
	{
		return
			(column_ == position.column_) &&
			(line_ == position.line_);
	}
	inline bool
	Position :: operator != (const Position& position) const {
		return !(operator == (position));
	}
	inline bool
	Position :: operator < (const Position& pos) const {
		return (line_ < pos.line_) || ((line_ == pos.line_) && (column_ < pos.column_));
	}
	inline bool
	Position :: operator <= (const Position& pos) const {
		return (line_ < pos.line_) || ((line_ == pos.line_) && (column_ <= pos.column_));
	}
	inline bool
	Position :: operator > (const Position& pos) const {
		return (line_ > pos.line_) || ((line_ == pos.line_) && (column_ > pos.column_));
	}
	inline bool
	Position :: operator >= (const Position& pos) const {
		return (line_ > pos.line_) || ((line_ == pos.line_) && (column_ >= pos.column_));
	}

	inline bool
	Position :: precedes (const Line_ line, const Column_ column) const {
		return (line_ < line) || ((line_ == line) && (column_ <= column));
	}
	inline bool
	Position :: follows (const Line_ line, const Column_ column) const {
		return (line_ > line) || ((line_ == line) && (column_ > column));
	}

	inline bool
	Position :: isUndefined() const
	{
		return
			(column_  == 0) &&
			(line_  == 0);
	}
	inline void
	Position :: setup (const Line_ line, const Column_ column)
	{
		column_ = column;
		line_   = line;
	}

	template<class S>
	inline void
	Position :: show (S& string) const
	{
		if (isUndefined()) {
			return;
		}
		if (line_ != Undefined<Line_> :: getValue ()) {
			string << tab << "line:   " << line_ + 1 << endLine;
		}
		if (column_ != Undefined<Column_> :: getValue()) {
			string << tab << "column: " << tab << column_ + 1 << endLine;
		}
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// nstd :: Object implementation
	void
	Position :: commitSuicide() {
		delete this;
	}
	Size_t
	Position :: getVolume() const {
		return 0;
	}
	Size_t
	Position :: getSizeOf() const {
		return sizeof (Position);
	}
	void
	Position :: show (String<>& string) const
	{
		//show<String<>&> (string);
		if (isUndefined()) {
			return;
		}
		if (line_ != Undefined<Line_> :: getValue ()) {
			string << tab << "line:   " << line_ + 1 << endLine;
		}
		if (column_ != Undefined<Column_> :: getValue()) {
			string << tab << "column: " << column_ + 1 << endLine;
		}
	}

	/****************************
	 *		Overloaded operators
	 ****************************/
}
}

#endif /*NSTD_LEXER_POSITION_CPP_*/
