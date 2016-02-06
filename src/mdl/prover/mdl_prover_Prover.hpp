/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_prover_Prover.hpp                                    */
/* Description:     class for the prover                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {

class Prover :
	public object :: Object,
	public Scalar<Prover> {
public :
	Prover (Format&);
	virtual ~ Prover();

	bool provingIsStarted() const;
	bool prove (const Time timeLimit, mdl :: proof :: Step* = NULL);
	bool reprove (const Time timeLimit, mdl :: proof :: Step* = NULL);

	// interactive proving
	void plantTree ();
	void growTree  ();
	void fellTree  ();
	void infoTree  (String&);
	void confirmProof();

	static void create (Format&);
	static Prover* get();
	static void release();
	static void clear();

	void showVolume (String&) const;
	void showTiming (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class T>
	bool proveTarget (const Time timeLimit, T*);

	template<class T>
	void plantTree();

	template<class T>
	void setupTarget (T*);

	template<class T>
	T* find();
	template<class T>
	T* findInComponents (mdl :: Components*);
	template<class T>
	T* findInTheorem (mdl :: Theorem*);
	template<class T>
	T* findInProof (mdl :: Proof*);

	Format format_;
	Format subFormat_;
	Format subSubFormat_;
	Run* run_;
	data :: Store dataStore_;
	static Prover* prover_;
};

}
}


