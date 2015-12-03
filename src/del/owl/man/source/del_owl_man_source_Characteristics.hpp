/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Characteristics.hpp                   */
/* Description:     manchester OWL characteristics source                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_CHARACTERISTICS_HPP_
#define DEL_OWL_MAN_SOURCE_CHARACTERISTICS_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Characteristics :
	public Object,
	public Scalar<Characteristics> {
public :
	Characteristics (const Location&);
	virtual ~ Characteristics();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Location location_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_CHARACTERISTICS_HPP_*/
