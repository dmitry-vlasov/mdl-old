/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Triple.hpp                       */
/* Description:     triple of parameters                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_PARAMETER_TRIPLE_HPP_
#define MDL_AUXILIARY_PARAMETER_TRIPLE_HPP_

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/auxiliary/parameter/mdl_auxiliary_parameter_Parameter.hpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

class Triple :
	public object :: Object,
	public Scalar<Triple> {
public :
	Triple (const Description*);
	Triple (const Description*, const value :: Real);
	Triple (const Triple&);
	virtual ~ Triple();

	value :: Real getValueHigh() const;
	value :: Real getValueMid() const;
	value :: Real getValueLow() const;
	bool isFlat() const;

	void iterateHighCase();
	void iterateMidCase();
	void iterateLowCase();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void initValues();

	const Description* description_;

	value :: Real valueHigh_;
	value :: Real valueMid_;
	value :: Real valueLow_;
};

}
}
}

#endif /*MDL_AUXILIARY_PARAMETER_TRIPLE_HPP_*/
