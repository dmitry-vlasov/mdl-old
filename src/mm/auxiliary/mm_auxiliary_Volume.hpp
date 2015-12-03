/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Volume.hpp                                  */
/* Description:     volume counters                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_VOLUME_HPP_
#define MM_AUXILIARY_VOLUME_HPP_

#include "interface/object/mm_interface_object_Object.hpp"
#include "mm.dpp"

namespace mm {
namespace auxiliary {

class Volume :
	public object :: Object,
	public Scalar<Volume> {
public :
	Volume (const Mm* const);
	virtual ~ Volume();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void calculate();
	void showVolume (String&) const;
	void showBalance (String&) const;

	Size_t parser_;
	Size_t source_;
	Size_t target_;
	Size_t sizeof_;

	Size_t names_;
	Size_t math_;
	Size_t auxiliary_;

	Size_t used_;
	Size_t allocated_;
	Ptrdiff_t delta_;

	bool calculated_;
	const Mm* const mm_;
};

}
}

#endif /* MM_AUXILIARY_VOLUME_HPP_ */
