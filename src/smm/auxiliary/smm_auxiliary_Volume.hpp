/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Volume.hpp                                 */
/* Description:     volume counters                                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_VOLUME_HPP_
#define SMM_AUXILIARY_VOLUME_HPP_

#include "smm/interface/object/smm_interface_object_Object.hpp"
#include "smm/smm.dpp"

namespace smm {
namespace auxiliary {

class Volume : public object :: Object, public Scalar<Volume> {
public :
	Volume (const Smm* const);
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
	Size_t sizeof_;

	Size_t math_;
	Size_t table_;
	Size_t stack_;

	Size_t used_;
	Size_t allocated_;
	Ptrdiff_t delta_;

	bool calculated_;
	const Smm* const smm_;
};

}
}

#endif /* SMM_AUXILIARY_VOLUME_HPP_ */
