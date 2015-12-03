/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Experience.hpp                 */
/* Description:     proposition usage experience                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_STATEMENT_EXPERIENCE_HPP_
#define MDL_FORM_HEADER_STATEMENT_EXPERIENCE_HPP_

namespace mdl {
namespace form {
namespace header {
namespace statement {

class Experience :
	public mdl :: statement :: Experience,
	public Scalar<Experience> {
public :
	Experience (const mdl :: Proposition*);
	virtual ~ Experience();

	// prover :: Experience interface
	virtual index :: Step getSize() const;
	virtual void addPositive (mdl :: proof :: Step*);
	virtual void addNegative (mdl :: proof :: Step*);
	virtual mdl :: vector :: proof :: Step& positiveSteps();
	virtual mdl :: vector :: proof :: Step& negativeSteps();
	virtual const mdl :: vector :: proof :: Step& positiveSteps() const;
	virtual const mdl :: vector :: proof :: Step& negativeSteps() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_STEP_VECTOR_CAPACITY = 32
	};

	const mdl :: Proposition* proposition_;
	mdl :: vector :: proof :: Step positiveSteps_;
	mdl :: vector :: proof :: Step negativeSteps_;
};

}
}
}
}

#endif /*MDL_FORM_HEADER_STATEMENT_EXPERIENCE_HPP_*/
