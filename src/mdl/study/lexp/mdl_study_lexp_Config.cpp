/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Config.cpp                                */
/* Description:     configuration of a trainee                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_LEXP_CONFIG_CPP_
#define MDL_STUDY_LEXP_CONFIG_CPP_

namespace mdl {
namespace study {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Config :: Config (const value :: Integer dimension) :
	parameterArray_ (dimension) {
	}
	inline
	Config :: Config (const Config& configuration) :
	parameterArray_ (configuration.getDimension())
	{
		for (value :: Integer i = 0; i < parameterArray_.getSize(); ++ i) {
			const Parameter* parameter = configuration.getParameter (i);
			if (parameter != NULL) {
				parameterArray_.getReference (i) = new Parameter (*parameter);
			}
		}
	}
	Config :: ~ Config() {
	}

	// Config implemntation
	value :: Integer
	Config :: getDimension() const {
		return parameterArray_.getSize();
	}
	Parameter*
	Config :: parameter (const value :: Integer i) {
		return parameterArray_.getValue (i);
	}
	const Parameter*
	Config :: getParameter (const value :: Integer i) const {
		return parameterArray_.getValue (i);
	}
	void
	Config :: setParameter (const value :: Integer i, Parameter* parameter) {
		parameterArray_.getReference (i) = parameter;
	}
	void
	Config :: copy (const Config& configuration)
	{
		for (value :: Integer i = 0; i < parameterArray_.getSize(); ++ i) {
			const Parameter* parameter = configuration.getParameter (i);
			parameterArray_.getValue (i)->copy (*parameter);
		}
	}

	// object :: Object implementation
	void
	Config :: commitSuicide() {
		delete this;
	}
	Size_t
	Config :: getVolume() const
	{
		Size_t volume = 0;
		volume += parameterArray_.getVolume();
		return volume;
	}
	Size_t
	Config :: getSizeOf() const {
		return sizeof (Config);
	}
	void
	Config :: show (String& string) const
	{
		for (value :: Integer i = 0; i < parameterArray_.getSize(); ++ i) {
			const Parameter* parameter = parameterArray_.getValue (i);
			//string << i << ": ";
			string << *parameter;
			if (i + 1 < parameterArray_.getSize()) {
				string << ", ";
			}
		}
	}
}
}
}

#endif /*MDL_STUDY_LEXP_CONFIG_CPP_*/
