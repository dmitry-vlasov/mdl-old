/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Comments.hpp                                  */
/* Description:     comment holder class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {

class Comments :
	public del :: Comments,
	public Scalar<Comments> {
public :
	typedef
		Lexer :: Comments_ :: Comment_
		Comment_;
	typedef
		Lexer :: Comments_ :: Index_
		Index_;

	Comments (const Lexer :: Comments_&, const bool = true);
	virtual ~ Comments();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		vector :: Vector
		<
			const String,
			storage :: ByPointer,
			allocator :: Heap
		>
		Vector_;
	Vector_ vector_;
	const bool multyLine_;
};

}
}


