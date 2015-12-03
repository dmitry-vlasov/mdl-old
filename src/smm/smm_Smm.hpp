/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_Smm.hpp                                              */
/* Description:     smm verifier                                             */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SMM_HPP_
#define SMM_SMM_HPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {

class Smm :
	public object :: Object,
	public Scalar<Smm> {
public :
	Smm();
	virtual ~ Smm();

	enum Status_ {
		SUCCESS            = Error :: NONE,
		LEXER_ERROR        = Error :: LEXER,
		PARSER_ERROR       = Error :: PARSER,
		SEMANTIC_ERROR     = Error :: SEMANTIC,
		VERIFICATION_ERROR = Error :: VERIFICATION,
		INPUT_ERROR        = Error :: INPUT,
		INIT_ERROR,
		RELEASE_ERROR,
		OUT_OF_MEMORY,
		GENERAL_FAILURE
	};

	void run ();

	Status_ getStatus() const;
	void showStart() const;
	void showFinal() const;

	static Status_ initMemory();
	static Status_ releaseMemory();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void process();
	void read();
	void verify();

	const String file_;
	const Path* path_;
	parser :: Source* parser_;
	const Source* source_;

	Timers  timers_;
	Volume  volume_;
	Status_ status_;

	friend class auxiliary :: Volume;
};

}

#endif /*SMM_SMM_HPP_*/
