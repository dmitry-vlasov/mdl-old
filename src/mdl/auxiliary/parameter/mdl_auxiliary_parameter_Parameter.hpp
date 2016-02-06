/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Parameter.hpp                    */
/* Description:     general parameter class template                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Object.hpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

class Parameter :
	public nstd :: Object,
	public Scalar<Parameter> {
public :
	Parameter (const Description*);
	Parameter (const Parameter&);
	virtual ~ Parameter();

	const Description* getDescription() const;

	value :: Real getValue() const;
	void setValue (const value :: Real);
	void setRealValue (const value :: Real);
	void setIntegerValue (const value :: Integer);

	void setDefaultValue();
	void setMaximumValue();
	void setMinimumValue();
	void setHighValue();
	void setLowValue();

	void operator = (const Parameter&);
	void copy (const Parameter&);

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	const Description* description_;
	value :: Real value_;
};

}
}
}


