/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_AxiomExtractor.cpp                          */
/* Description:     axiom extractor                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_AXIOM_EXTRACTOR_CPP_
#define MM_AUXILIARY_AXIOM_EXTRACTOR_CPP_

#include "lexer/mm_lexer.hpp"
#include "auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	void
	AxiomExtractor :: run ()
	{
		openSource();
		openOutput();

		Lexer :: nextToken();

		while (true) {
			parseSimpleNodeForAxioms();
			Lexer :: nextToken();
			if (Lexer :: tokenType() == Lexer :: EOF_) {
				if (Lexer :: pop()) {
					Lexer :: nextToken();
				} else {
					break;
				}
			}
		}

		closeOutput();
	}

	/// nstd :: Static implementation
	void
	AxiomExtractor :: initRaw () {
		labelToken_.init (INITIAL_LABEL_TOKEN_CAPACITY);
	}
	void
	AxiomExtractor :: showRaw (nstd :: String&) {
	}
	Size_t
	AxiomExtractor :: getRawVolume() {
		return labelToken_.volume();
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	AxiomExtractor :: openSource ()
	{
		bool fileOpened = Lexer :: push (Config :: sourceName.c_str());
		if (!fileOpened) {
			throw new Error (Error :: INPUT, "file not found or empty.\n");
		}
	}
	void
	AxiomExtractor :: openOutput () {
		fileStream_.open (Config :: extractionTarget().path());
	}
	void
	AxiomExtractor :: closeOutput () {
		fileStream_.close ();
	}

using nstd :: endl;

	void
	AxiomExtractor :: parseBlockForAxioms ()
	{
		Lexer :: nextToken();
		while (Lexer :: tokenType() != Lexer :: BLOCK_END) {
			parseSimpleNodeForAxioms();
			Lexer :: nextToken();
		}
	}
	void
	AxiomExtractor :: parseSimpleNodeForAxioms()
	{
		switch (Lexer :: tokenType()) {
		case Lexer :: CONSTANT :
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				Lexer :: nextToken();
			}
			break;
		case Lexer :: VARIABLE :
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				Lexer :: nextToken();
			}
			break;
		case Lexer :: DISJOINTED :
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				Lexer :: nextToken();
			}
			break;
		case Lexer :: BLOCK_BEGIN :
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: BLOCK_END) {
				parseSimpleNodeForAxioms();
				Lexer :: nextToken();
			}
			break;
		case Lexer :: COMMENT :
			break;
		case Lexer :: INCLUSION_BEGIN : {
			Lexer :: nextInclusion();
			Lexer :: push (Lexer :: token());
			break;
		}
		case Lexer :: EOF_ : {
			if (!Lexer :: pop ()) {
				throw new Error (Error :: PARSER, "unxepected EOF in the block.\n");
			}
			break;
		}
		case Lexer :: LITERAL :
			labelToken_.copy (Lexer :: token());
			parseLabeledNodeForAxioms ();
			break;
		default :
			Error* error = new Error (Error :: MISC);
			error->message() << "unexpected token: "<< Lexer :: token() << endl;
			error->message() << " should be one of : $c, $v, $d, ${, $( or label token" << endl;
			throw error;
			break;
		}
	}

	void
	AxiomExtractor :: parseLabeledNodeForAxioms ()
	{
		Lexer :: nextToken();	// label
		switch (Lexer :: tokenType()) {
		case Lexer :: FLOATING : {
			Lexer :: nextToken(); // type
			Lexer :: nextToken(); // variable
			Lexer :: nextToken(); // $.
			break;
		}
		case Lexer :: ESSENTIAL : {
			//fileStream << labelToken << " $e ";
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				//fileStream << Lexer :: token << " ";
				Lexer :: nextToken();
			}
			//fileStream << "$." << NEW_LINE;
			break;
		}
		case Lexer :: ASSERTION : {
			fileStream_ << labelToken_ << " $a ";
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				fileStream_ << Lexer :: token() << " ";
				Lexer :: nextToken();
			}
			fileStream_ << "$." << NEW_LINE;
			break;
		}
		case Lexer :: THEOREM : {
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: PROOF) {
				Lexer :: nextToken();
			}
			Lexer :: nextToken();
			while (Lexer :: tokenType() != Lexer :: END) {
				Lexer :: nextToken();
			}
			break;
		}
		default :
			Error* error = new Error (Error :: MISC);
			error->message() << "wrong token type: " << Lexer :: token() << endl;
			error->message() << " should be one of : $f, $e, $a, $p" << endl;
			throw endl;
			break;
		}
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	String
		AxiomExtractor :: labelToken_;

	nstd :: OutputFileStream
		AxiomExtractor :: fileStream_;
}
}

#endif /*MM_AUXILIARY_AXIOM_EXTRACTOR_CPP_*/
