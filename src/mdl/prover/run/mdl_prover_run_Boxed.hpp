/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_run_Boxed.hpp                                 */
/* Description:     main prover tree class using boxed memory                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_RUN_BOXED_HPP_
#define MDL_PROVER_RUN_BOXED_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/interface/mdl_prover_interface.hpp"

namespace mdl {
namespace prover {
namespace run {

class Boxed :
	public Run,
	public Scalar<Boxed> {
public :
	typedef
		typename allocator :: Boxed
		Allocator_;
	typedef
		typename tree :: Tree<Allocator_>
		Tree_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Boxed (Format&, Format&, mdl :: proof :: Question*);
	virtual ~ Boxed();

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

#endif /*MDL_PROVER_RUN_BOXED_HPP_*/
