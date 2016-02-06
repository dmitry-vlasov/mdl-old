/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Comments.hpp                                  */
/* Description:     container for comments                                   */
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

template<class A>
class Comments : public Object {
public :
	typedef A Allocator_;
	typedef String<A> Comment_;
	typedef Size_t Index_;

	Comments();
	virtual ~ Comments();

	Comment_* push();
	const Comment_* get (const Index_) const;
	void clear();
	Index_ getSize() const;
	bool isEmpty() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	typedef
		container :: Vector
		<
			Comment_,
			container :: storage :: ByPointer,
			Allocator_
		>
		Vector_;

	enum {
		INITIAL_VECTOR_CAPACITY = 16,
		INITIAL_COMMENT_CAPACITY = 1024
	};
	Vector_ vector_;
};

}
}


