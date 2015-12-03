/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Comments.hpp                                    */
/* Description:     comment holder class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_COMMENTS_HPP_
#define MDL_FORM_COMMENTS_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace form {

class Comments :
	public mdl :: Comments,
	public Scalar<Comments> {
public :
	typedef
		Lexer :: Comments_ :: Comment_
		Comment_;
	typedef
		Lexer :: Comments_ :: Index_
		Index_;

	Comments (const Lexer :: Comments_&, const bool multyLine = true);
	Comments (const char* comment, const bool multyLine = true);
	Comments (const bool multyLine = true);
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
			String,
			storage :: ByPointer,
			allocator :: Heap
		>
		Vector_;
	enum {
		INITIAL_VECTOR_CAPACITY = 4
	};

	Vector_ vector_;
	const bool multyLine_;
};

}
}

#endif /*MDL_FORM_COMMENTS_HPP_*/
