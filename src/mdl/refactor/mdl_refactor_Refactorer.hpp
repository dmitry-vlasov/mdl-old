/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_Refactorer.hpp                              */
/* Description:     class for the refactor                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REFACTORER_HPP_
#define MDL_REFACTOR_REFACTORER_HPP_

namespace mdl {
namespace refactor {

class Refactorer :
	public object :: Object,
	public Scalar<Refactorer> {
public :
	Refactorer (Format&);
	virtual ~ Refactorer();

	void refactor (mdl :: Source*);

	static void create (Format&);
	static Refactorer* get();
	static void release();
	static void clear();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void totalStructureVerification() const;

	void rename (mdl :: Source*);
	void move (mdl :: Source*);
	void reduce (mdl :: Source*);
	void reduce (mdl :: Theorem*);

	void showStatistics();

	Format format_;
	Format subFormat_;

	redundant :: Hypotheses* redundantHypotheses_;
	redundant :: Steps*      redundantSteps_;
	redundant :: Variables*  redundantVariables_;

	// Statistics data
	value :: Integer duplicateHypothesis_;
	value :: Integer unusedHypothesis_;
	value :: Integer duplicateProofSteps_;
	value :: Integer unusedProofSteps_;
	value :: Integer unusedVariables_;

	static Refactorer* refactor_;
};

}
}

#endif /*MDL_REFACTOR_REFACTORER_HPP_*/
