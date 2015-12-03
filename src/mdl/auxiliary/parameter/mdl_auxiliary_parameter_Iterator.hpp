/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Iterator.hpp                     */
/* Description:     general parameter vector iterator                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_PARAMETER_ITERATOR_HPP_
#define MDL_AUXILIARY_PARAMETER_ITERATOR_HPP_

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/auxiliary/parameter/mdl_auxiliary_parameter.dpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

class Iterator :
	public nstd :: Object,
	public Scalar<Iterator> {
public :
	Iterator (const mdl :: parameter :: vector :: Description*);
	virtual ~ Iterator();

	bool operator ++();
	value :: Real getValue (const value :: Integer) const;
	vector :: value :: Real& parameters();

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	bool increment (const value :: Integer = 0);

	const mdl :: parameter :: vector :: Description* descriptionVector_;
	const value :: Integer dimension_;
	vector :: value :: Real parameters_;
};

}
}
}

#endif /*MDL_AUXILIARY_PARAMETER_ITERATOR_HPP_*/
