/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Contents.cpp                                  */
/* Description:     theory contents parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_CONTENTS_CPP_
#define MDL_PARSER_CONTENTS_CPP_

namespace mdl {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Contents :: Contents() :
	constantParser_ (new parser :: Constant()),
	typeParser_ (new parser :: Type()),
	ruleParser_ (new parser :: Rule()),
	axiomParser_ (new parser :: Axiom()),
	definitionParser_ (new parser :: Definition()),
	theoremParser_ (new  parser :: Theorem()),
	proofParser_ (new  parser :: Proof()),
	problemParser_ (new parser :: Problem()),
	theoryParser_ (new parser :: Theory()),
	evaluationParser_ (new parser :: Evaluation()),
	contentsParser_ (NULL),

	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	contents_ (NULL),
	downTheory_ (NULL) {
	}
	Contents :: ~ Contents()
	{
		deleteAggregateObject (constantParser_);
		deleteAggregateObject (typeParser_);
		deleteAggregateObject (ruleParser_);
		deleteAggregateObject (axiomParser_);
		deleteAggregateObject (definitionParser_);
		deleteAggregateObject (theoremParser_);
		deleteAggregateObject (proofParser_);
		deleteAggregateObject (problemParser_);
		deleteAggregateObject (theoryParser_);
		deleteAggregateObject (evaluationParser_);
		deleteAggregateObject (contentsParser_);
	}

	mdl :: Contents*
	Contents :: parse (Lexer* lexer, mdl :: Theory* upTheory)
	{
		location_ = lexer->getLocation();

		lexer->scan<Token :: OF>();
		lexer->scan<Token :: NAME>();
		name_ = Table :: names()->find (lexer->getToken());
		lexer->scan<Token :: OPEN_BRACE>();

		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		contents_ = new form :: Contents (location_, comments_, name_, upTheory);

		downTheory_ = contents_->innerTheory_;

		while (true) {
			lexer->scan
			<
				Token :: CONSTANT,
				Token :: TYPE,
				Token :: RULE,
				Token :: AXIOM,
				Token :: DEFINITION,
				Token :: THEOREM,
				Token :: PROOF,
				Token :: PROBLEM,
				Token :: THEORY,
				Token :: EVALUATION,
				Token :: CONTENTS,
				Token :: CLOSE_BRACE
			>();
			switch (lexer->getTokenType()) {
			case Token :: CONSTANT :
				contents_->addComponentLast (constantParser_->parse (lexer, downTheory_));
				break;
			case Token :: TYPE :
				contents_->addComponentLast (typeParser_->parse (lexer, downTheory_));
				break;
			case Token :: RULE :
				contents_->addComponentLast (ruleParser_->parse (lexer, downTheory_));
				break;
			case Token :: AXIOM :
				contents_->addComponentLast (axiomParser_->parse (lexer, downTheory_));
				break;
			case Token :: DEFINITION :
				contents_->addComponentLast (definitionParser_->parse (lexer, downTheory_));
				break;
			case Token :: THEOREM :
				contents_->addComponentLast (theoremParser_->parse (lexer, downTheory_));
				break;
			case Token :: PROOF :
				contents_->addComponentLast (proofParser_->parse (lexer, downTheory_));
				break;
			case Token :: PROBLEM :
				contents_->addComponentLast (problemParser_->parse (lexer, downTheory_));
				break;
			case Token :: THEORY :
				contents_->addComponentLast (theoryParser_->parse (lexer, downTheory_));
				break;
			case Token :: EVALUATION :
				contents_->addComponentLast (evaluationParser_->parse (lexer, downTheory_));
				break;
			case Token :: CONTENTS :
				if (contentsParser_ == NULL) {
					contentsParser_ = new parser :: Contents ();
				}
				contents_->addComponentLast (contentsParser_->parse (lexer, downTheory_));
				break;
			case Token :: CLOSE_BRACE :
				return contents_;
			default :
				return NULL;
			}
		}
	}

	// object :: Object implementation
	void
	Contents :: commitSuicide() {
		delete this;
	}
	Size_t
	Contents :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (constantParser_);
		volume += getAggregateVolume (typeParser_);
		volume += getAggregateVolume (ruleParser_);
		volume += getAggregateVolume (axiomParser_);
		volume += getAggregateVolume (definitionParser_);
		volume += getAggregateVolume (theoremParser_);
		volume += getAggregateVolume (proofParser_);
		volume += getAggregateVolume (problemParser_);
		volume += getAggregateVolume (theoryParser_);
		volume += getAggregateVolume (evaluationParser_);
		volume += getAggregateVolume (contentsParser_);
		return volume;
	}
	Size_t
	Contents :: getSizeOf() const {
		return sizeof (Contents);
	}
	void
	Contents :: show (String&) const {
	}
}
}

#endif /*MDL_PARSER_CONTENTS_CPP_*/
