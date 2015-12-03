/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Location.hpp                                  */
/* Description:     location in input                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_LOCATION_HPP_
#define NSTD_LEXER_LOCATION_HPP_

#include "lexer/nstd_lexer_Indent.hpp"
#include "lexer/nstd_lexer_Position.hpp"
#include "lexer/nstd_lexer_Buffer.hpp"

namespace nstd {
namespace lexer {

template<class S = Source<Buffer<> :: DEFAULT_SIZE > >
class Location : public Object {
public :
	typedef S Source_;

	Location();
	Location (const Indent);
	Location (const Source_* const);
	Location (const Location&);

	Position& position();
	Indent& indent();
	const Position& getPosition() const;
	const Indent& getIndent() const;
	bool isTop() const;
	const char* file() const;

	bool operator == (const Location&) const;
	bool operator != (const Location&) const;
	void operator = (const Location&);
	bool isNearestTo (const Position&) const;
	void markupPosition();

	template<class T>
	void show (T&) const;
	template<class T>
	void showAttributes (T&) const;

	static Size_t getPositionListVolume();
	static void deletePositionList();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	void clear();
	void newLine();

	template<int>
	friend class Source;

	const Source_* source_;
	Indent indent_;
	Position position_;

	struct PositionNode :
		public memory :: storage :: Scalar
		<
			PositionNode,
			memory :: allocator :: Standard
		> {
		Position position_;
		PositionNode* prev_;
		PositionNode* next_;

		PositionNode (const Position&);
	};

	PositionNode* node_;

	// These positions are globals of top source
	static PositionNode* first_;
	static PositionNode* last_;
};

}
}

#endif /*NSTD_LEXER_LOCATION_HPP_*/
