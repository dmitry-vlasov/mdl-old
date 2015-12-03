/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Map.hpp                        */
/* Description:     abstract interface for maps                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_QUEUE_MAP_HPP_
#define DEL_INTERFACE_MODEL_QUEUE_MAP_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/model/queue/del_interface_model_queue.dpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

class Map : public Object {
public :
	virtual const del :: model :: queue :: set :: Range* map (Domain*) const = 0;
	virtual del :: model :: queue :: set :: Range* map (Domain*) = 0;
	virtual del :: model :: queue :: set :: Range* map (const value :: Variable) = 0;
	virtual del :: model :: queue :: set :: Range* map (const value :: Variable, const value :: Relation) = 0;
};

}
}
}
}

#endif /*DEL_INTERFACE_MODEL_QUEUE_MAP_HPP_*/
