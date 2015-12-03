/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Description.hpp                  */
/* Description:     general parameter description template                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_PARAMETER_DESCRIPTION_HPP_
#define MDL_AUXILIARY_PARAMETER_DESCRIPTION_HPP_

#include "mdl/interface/object/mdl_interface_object_Object.hpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

class Description :
	public nstd :: Object,
	public Scalar<Description> {
public :
	Description (const Description&);
	Description
	(
		const value :: Real defaultValue,
		const value :: Real minimumValue,
		const value :: Real maximumValue,
		const value :: Real quantumValue,
		const char* name = "",
		const bool isReal = true
	);
	virtual ~ Description();

	bool isReal() const;
	bool isInteger() const;

	value :: Real getMinimumValue() const;
	value :: Real getMaximumValue() const;
	value :: Real getQuantumValue() const;
	value :: Real getDefaultValue() const;
	const char* getName() const;
	void operator = (const Description&);

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	const bool isReal_;
	const char* name_;
	value :: Real defaultValue_;
	value :: Real minimumValue_;
	value :: Real maximumValue_;
	value :: Real quantumValue_;
};

}
}
}

#endif /*MDL_AUXILIARY_PARAMETER_DESCRIPTION_HPP_*/
