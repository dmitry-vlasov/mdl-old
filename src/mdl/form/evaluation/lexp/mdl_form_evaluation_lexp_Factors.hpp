/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Factors.hpp                     */
/* Description:     factors for distance calculation                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_FACTORS_HPP_
#define MDL_FORM_EVALUATION_LEXP_FACTORS_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

class Factors :
	public object :: Object,
	public Scalar<Factors> {
public :
	Factors();
	Factors
	(
		const value :: Real alpha,
		const value :: Real beta
	);
	Factors (const Factors&);
	virtual ~ Factors();

	value :: Real getAlpha() const;
	value :: Real getBeta() const;
	value :: Real getGamma (const value :: Integer) const;

	void setAlpha (const value :: Real);
	void setBeta (const value :: Real);
	void setGamma ();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_FACTORS_CAPACITY = 8
	};

	value :: Real  alpha_;
	value :: Real  beta_;
	vector :: Real gamma_;

	static value :: Real epsilon_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_FACTORS_HPP_*/
