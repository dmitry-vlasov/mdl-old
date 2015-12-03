/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Volume.hpp                                 */
/* Description:     class for program data volume counters                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_VOLUME_HPP_
#define DEL_AUXILIARY_VOLUME_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/del.dpp"

namespace del {
namespace auxiliary {

class Volume :
	public Object,
	public Scalar<Volume> {
public :
	Volume (const Del* const);
	virtual ~ Volume();

	void countModel (Model*);

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

	Size_t model_;
	Size_t variables_;
	Size_t conceptMap_;
	Size_t relationMap_;

	Size_t statistics_;

	Size_t used_;
	Size_t allocated_;
	Ptrdiff_t delta_;

	bool calculated_;
	const Del* const del_;
};

}
}

#endif /*DEL_AUXILIARY_VOLUME_HPP_*/
