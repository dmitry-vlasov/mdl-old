/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Config.hpp                                */
/* Description:     configuration of a trainee                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace study {
namespace lexp {

class Config :
	public object :: Object,
	public Scalar<Config> {
public :
	Config (const value :: Integer);
	Config (const Config&);
	virtual ~ Config();

	// Config interface
	value :: Integer getDimension() const;
	Parameter* parameter (const value :: Integer);
	const Parameter* getParameter (const value :: Integer) const;
	void setParameter (const value :: Integer, Parameter*);
	void copy (const Config&);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		array :: Array
		<
			Parameter,
			storage :: ByPointer,
			allocator :: Heap
		>
		ParameterArray_;

	ParameterArray_ parameterArray_;
};

}
}
}


