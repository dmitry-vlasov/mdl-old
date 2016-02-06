/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Statistics.hpp                             */
/* Description:     class for program data statistics counters               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/del.dpp"

namespace del {
namespace auxiliary {

class Statistics :
	public Object,
	public Scalar<Statistics> {
public :
	class Data;

	Statistics();
	virtual ~ Statistics();

	Data* data();
	void push();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		vector :: Vector
		<
			Data,
			storage :: ByPointer,
			allocator :: Heap
		>
		DataVector_;

	DataVector_ dataVector_;
	Data* data_;
	enum {
		INITIAL_DATA_VECTOR_CAPACITY = 32
	};
};

}
}


