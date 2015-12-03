/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Similarity.hpp                     */
/* Description:     class which represents similarity of expressions         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SIMIFY_SIMILARITY_HPP_
#define MDL_EXPRESSION_SIMIFY_SIMILARITY_HPP_

namespace mdl {
namespace expression {
namespace simify {

template<class U>
class Similarity {
public :
	typedef U Unit_;
	typedef
		typename Unit_ :: InverseUnit_
		InverseUnit_;
	typedef
		Similarity<InverseUnit_>
		InverseSimilarity_;

	Similarity ();
	Similarity (const Similarity&);
	Similarity (const Unit_&);

	bool none() const;
	value :: Integer getDirect() const;
	value :: Integer getInverse() const;
	InverseSimilarity_ inverse() const;

	void operator = (const Similarity&);
	void operator += (const Similarity);

private :
	friend class Similarity<InverseUnit_>;

	Similarity (const value :: Integer, const value :: Integer);

	value :: Integer direct_;
	value :: Integer inverse_;
};

}
}
}

#endif /*MDL_EXPRESSION_SIMIFY_SIMILARITY_HPP_*/
