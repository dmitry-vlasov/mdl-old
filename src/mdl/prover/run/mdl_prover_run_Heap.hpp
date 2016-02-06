/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_run_Heap.hpp                                  */
/* Description:     main prover class using heap memory                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/interface/mdl_prover_interface.hpp"

namespace mdl {
namespace prover {
namespace run {

class Heap :
	public Run,
	public Scalar<Heap> {
public :
	typedef
		typename allocator :: Heap
		Allocator_;
	typedef
		typename tree :: Tree<Allocator_>
		Tree_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Heap (Format&, Format&, mdl :: proof :: Question*);
	virtual ~ Heap();

	// prover :: Run interface
	virtual bool prove (const Time);
	virtual void start (String& message);
	virtual void grow  ();
	virtual void stop  ();
	virtual void info  (String&);
	virtual void confirm ();
	virtual bool isProved();
	virtual void showVolume (String&) const;
	virtual void showTiming (String&) const;
	virtual Data* getData() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Format& format_;
	Format& subFormat_;
	mdl :: proof :: Question* question_;
	Tree_*  tree_;
	mutable Data* data_;
};

}
}
}


