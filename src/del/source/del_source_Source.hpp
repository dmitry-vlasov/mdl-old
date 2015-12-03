/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Source.hpp                                    */
/* Description:     source class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_SOURCE_HPP_
#define DEL_SOURCE_SOURCE_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Source :
	public del :: Source,
	public Scalar<Source> {
public :
	Source
	(
		const Lexer* const,
		const del :: Comments*,
		const Path&,
		const Path&
	);
	Source
	(
		const Lexer* const,
		const del :: Comments*,
		const Path&
	);
	Source (const Path&);
	Source ();
	virtual ~ Source();

	static Source* createRandom ();
	static Source* createRandom (const value :: Integer theoryCount);

	// del :: Source interface
	virtual void addAssertion (const del :: Assertion*);
	virtual void addTheory (const del :: Theory*);
	virtual void addQuestion (const del :: Question*);
	virtual void addAnswer (const del :: Answer*);
	virtual void addSignature (const del :: Signature*);
	virtual void addComments (const del :: Comments*);
	virtual void addDecompose (const del :: Decompose*);
	virtual void addDecomposition (const del :: Decomposition*);
	virtual void addMinimize (const del :: Minimize*);
	virtual void addMinimization (const del :: Minimization*);
	virtual void solve();
	virtual void decompose();
	virtual void minimize();
	virtual void verify();
	virtual void write() const;
	virtual bool isSolvable() const;
	virtual bool isDecomposable() const;
	virtual bool isMinimizable() const;
	virtual bool isVerifiable() const;
	virtual bool isWritable() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	// translation routines
	void writeToDelFormat() const;
	void writeToManFormat() const;
	void writeToFuncFormat() const;

	const Lexer* const lexer_;
	mutable Path sourcePath_;
	mutable Path targetPath_;
	const del :: Comments* commentsStart_;
	const del :: Comments* commentsEnd_;
	vector :: Writable components_;
	vector :: Question questions_;
	vector :: Decompose decomposes_;
	vector :: Minimize  minimizes_;
	vector :: Assertion assertions_;
	vector :: Theory    theories_;
	vector :: Decomposition decompositions_;
	mutable Output* output_;
	enum {
		INITIAL_COMPONENTS_CAPACITY = 256,
		INITIAL_QUESTIONS_CAPACITY = 256,
		INITIAL_DECOMPOSES_CAPACITY = 256,
		INITIAL_MINIMIZES_CAPACITY = 256,
		INITIAL_ASSERTIONS_CAPACITY = 256,
		INITIAL_THEORIES_CAPACITY = 256,
		INITIAL_DECOMPOSITIONS_CAPACITY = 256
	};
};

}
}

#endif /*DEL_SOURCE_SOURCE_HPP_*/
