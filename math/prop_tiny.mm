$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Pre-logic
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

  $( Declare the primitive constant symbols for propositional calculus. $)
  $c ( $.  $( Left parenthesis $)
  $c ) $.  $( Right parenthesis $)
  $c -> $. $( Right arrow (read:  "implies") $)
  $c -. $. $( Right handle (read:  "not") $)
  $c wff $. $( Well-formed formula symbol (read:  "the following symbol
               sequence is a wff") $)
  $c |- $. $( Turnstile (read:  "the following symbol sequence is provable" or
              'a proof exists for") $)

  $( Introduce some variable names we will use to represent well-formed
     formulas (wff's). $)
  $v ph $. $( Greek phi $)
  $v ps $.  $( Greek psi $)
  $v ch $.  $( Greek chi $)
  $v th $.  $( Greek theta $)
  $v ta $.  $( Greek tau $)

  $( Specify some variables that we will use to represent wff's.
     The fact that a variable represents a wff is relevant only to a theorem
     referring to that variable, so we may use $f hypotheses.  The symbol
     ` wff ` specifies that the variable that follows it represents a wff. $)
  $( Let variable ` ph ` be a wff. $)
  wph $f wff ph $.
  $( Let variable ` ps ` be a wff. $)
  wps $f wff ps $.
  $( Let variable ` ch ` be a wff. $)
  wch $f wff ch $.
  $( Let variable ` th ` be a wff. $)
  wth $f wff th $.
  $( Let variable ` ta ` be a wff. $)
  wta $f wff ta $.

$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Propositional calculus
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Recursively define primitive wffs for propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( If ` ph ` is a wff, so is ` -. ph ` or "not ` ph ` ."  Part of the
     recursive definition of a wff (well-formed formula).  In classical logic
     (which is our logic), a wff is interpreted as either true or false.
     So if ` ph ` is true, then ` -. ph ` is false; if ` ph ` is false, then
     ` -. ph ` is true.  Traditionally, Greek letters are used to represent
     wffs, and we follow this convention.  In propositional calculus, we define
     only wffs built up from other wffs, i.e. there is no starting or "atomic"
     wff.  Later, in predicate calculus, we will extend the basic wff
     definition by including atomic wffs ( ~ weq and ~ wel ). $)
  wn $a wff -. ph $.

  $( If ` ph ` and ` ps ` are wff's, so is ` ( ph -> ps ) ` or " ` ph ` implies
     ` ps ` ."  Part of the recursive definition of a wff.  The resulting wff
     is (interpreted as) false when ` ph ` is true and ` ps ` is false; it is
     true otherwise.  (Think of the truth table for an OR gate with input
     ` ph ` connected through an inverter.)  The left-hand wff is called the
     antecedent, and the right-hand wff is called the consequent.  In the case
     of ` ( ph -> ( ps -> ch ) ) ` , the middle ` ps ` may be informally called
     either an antecedent or part of the consequent depending on context. $)
  wi $a wff ( ph -> ps ) $.

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        The axioms of propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $(
     Postulate the three axioms of classical propositional calculus.
  $)

  $( Axiom _Simp_.  Axiom A1 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  The 3 axioms are also given as Definition 2.1
     of [Hamilton] p. 28.  This axiom is called _Simp_ or "the principle of
     simplification" in _Principia Mathematica_ (Theorem *2.02 of
     [WhiteheadRussell] p. 100) because "it enables us to pass from the joint
     assertion of ` ph ` and ` ps ` to the assertion of ` ph ` simply."

     _General remarks_:  Propositional calculus (axioms ~ ax-1 through ~ ax-3
     and rule ~ ax-mp ) can be thought of as asserting formulas that are
     universally "true" when their variables are replaced by any combination
     of "true" and "false."  Propositional calculus was first formalized by
     Frege in 1879, using as his axioms (in addition to rule ~ ax-mp ) the
     wffs ~ ax-1 , ~ ax-2 , ~ pm2.04 , ~ con3 , ~ nega , and ~ negb .  Around
     1930, Lukasiewicz simplified the system by eliminating the third (which
     follows from the first two, as you can see by looking at the proof of
     ~ pm2.04 ) and replacing the last three with our ~ ax-3 .  (Thanks to Ted
     Ulrich for this information.)

     The theorems of propositional calculus are also called _tautologies_.
     Tautologies can be proved very simply using truth tables, based on the
     true/false interpretation of propositional calculus.  To do this, we
     assign all possible combinations of true and false to the wff variables
     and verify that the result (using the rules described in ~ wi and ~ wn )
     always evaluates to true.  This is called the _semantic_ approach.  Our
     approach is called the _syntactic_ approach, in which everything is
     derived from axioms.  A metatheorem called the Completeness Theorem for
     Propositional Calculus shows that the two approaches are equivalent and
     even provides an algorithm for automatically generating syntactic proofs
     from a truth table.  Those proofs, however, tend to be long, and the
     much shorter proofs that we show here were found manually.  Truth tables
     grow exponentially with the number of variables, but it is unknown if the
     same is true of proofs - an answer to this would resolve the P=NP
     conjecture in complexity theory. $)
  ax-1 $a |- ( ph -> ( ps -> ph ) ) $.
  $( [ ?] $) $( [ ?] $)

  $( Axiom _Frege_.  Axiom A2 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It "distributes" an antecedent over two
     consequents.  This axiom was part of Frege's original system and is known
     as _Frege_ in the literature.  It is also proved as Theorem *2.77 of
     [WhiteheadRussell] p. 108.  The other direction of this axiom also
     turns out to be true, as demonstrated by ~ pm5.41 . $)
  ax-2 $a |- ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ps ) -> ( ph -> ch ) ) ) $.

  $( Axiom _Transp_.  Axiom A3 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It swaps or "transposes" the order of the
     consequents when negation is removed.  An informal example is that the
     statement "if there are no clouds in the sky, it is not raining" implies
     the statement "if it is raining, there are clouds in the sky."  This
     axiom is called _Transp_ or "the principle of transposition" in
     _Principia Mathematica_ (Theorem *2.17 of [WhiteheadRussell] p. 103).
     We will also use the term "contraposition" for this principle, although
     the reader is advised that in the field of philosophical logic,
     "contraposition" has a different technical meaning. $)
  ax-3 $a |- ( ( -. ph -> -. ps ) -> ( ps -> ph ) ) $.

  $(
     Postulate the modus ponens rule of inference.
  $)

  ${
    $( Minor premise for modus ponens. $)
    min $e |- ph $.
    $( Major premise for modus ponens. $)
    maj $e |- ( ph -> ps ) $.
    $( Rule of Modus Ponens.  The postulated inference rule of propositional
       calculus.  See e.g. Rule 1 of [Hamilton] p. 73.  The rule says, "if
       ` ph ` is true, and ` ph ` implies ` ps ` , then ` ps ` must also be
       true."  This rule is sometimes called "detachment," since it detaches
       the minor premise from the major premise. $)
    ax-mp $a |- ps $.
  $}

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical implication
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

$( The results in this section make use of the first 2 axioms only.  In
   an implication, the wff before the arrow is called the "antecedent"
   and the wff after the arrow is called the "consequent." $)

$( We will use the following descriptive terms very loosely:  A "theorem"
   usually has no $e hypotheses.  An "inference" has one or more $e hypotheses.
   A "deduction" is an inference in which the hypotheses and the result
   share the same antecedent. $)

  ${
    $( Premise for ~ a1i . $)
    a1i.1 $e |- ph $.
    $( Inference derived from axiom ~ ax-1 .  See ~ a1d for an explanation of
       our informal use of the terms "inference" and "deduction." $)
    a1i $p |- ( ps -> ph ) $=
      wph wps wph wi a1i.1 wph wps ax-1 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ a2i . $)
    a2i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference derived from axiom ~ ax-2 . $)
    a2i $p |- ( ( ph -> ps ) -> ( ph -> ch ) ) $=
      wph wps wch wi wi wph wps wi wph wch wi wi a2i.1 wph wps wch ax-2 ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( First of 2 premises for ~ syl . $)
    syl.1 $e |- ( ph -> ps ) $.
    $( Second of 2 premises for ~ syl . $)
    syl.2 $e |- ( ps -> ch ) $.
    $( An inference version of the transitive laws for implication ~ imim2 and
       ~ imim1 , which Russell and Whitehead call "the principle of the
       syllogism...because...the syllogism in Barbara is derived from them"
       (quote after Theorem *2.06 of [WhiteheadRussell] p. 101).  Some authors
       call this law a "hypothetical syllogism."

       (A bit of trivia:  this is the most commonly referenced assertion in our
       database.  In second place is ~ ax-mp , followed by ~ visset , ~ bitr ,
       ~ imp , and ~ ex .  The Metamath program command 'show usage' shows the
       number of references.) $)
    syl $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi syl.1 wph wps wch wps wch wi wph syl.2 a1i a2i
      ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ com12 .  See ~ pm2.04 for the theorem form. $)
    com12.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference that swaps (commutes) antecedents in an implication. $)
    com12 $p |- ( ps -> ( ph -> ch ) ) $=
      wps wph wps wi wph wch wi wps wph ax-1 wph wps wch com12.1 a2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    a1d.1 $e |- ( ph -> ps ) $.
    $( Deduction introducing an embedded antecedent.  (The proof was revised by
       Stefan Allan, 20-Mar-06.)

       _Naming convention_:  We often call a theorem a "deduction" and suffix
       its label with "d" whenever the hypotheses and conclusion are each
       prefixed with the same antecedent.  This allows us to use the theorem in
       places where (in traditional textbook formalizations) the standard
       Deduction Theorem would be used; here ` ph ` would be replaced with a
       conjunction ( ~ df-an ) of the hypotheses of the would-be deduction.  By
       contrast, we tend to call the simpler version with no common antecedent
       an "inference" and suffix its label with "i"; compare theorem ~ a1i .
       Finally, a "theorem" would be the form with no hypotheses; in this case
       the "theorem" form would be the original axiom ~ ax-1 .  In
       propositional calculus we usually prove the theorem form first without a
       suffix on its label (e.g.  ~ pm2.43 vs.  ~ pm2.43i vs.  ~ pm2.43d ), but
       (much) later we often suffix the theorem form's label with "t" as in
       ~ negnegt vs. ~ negneg , especially when our "weak deduction theorem"
       ~ dedth is used to prove the theorem form from its inference form.  When
       an inference is converted to a theorem by eliminating an "is a set"
       hypothesis, we sometimes suffix the theorem form with "g" (for somewhat
       overstated "generalized") as in ~ uniex vs.  ~ uniexg . $)
    a1d $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wch wps wi a1d.1 wps wch ax-1 syl $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    a2d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Deduction distributing an embedded antecedent. $)
    a2d $p |- ( ph -> ( ( ps -> ch ) -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wps wch wi wps wth wi wi a2d.1 wps wch wth ax-2 syl
      $.
      $( [23-Jun-1994] $)
  $}

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.05 of
     [WhiteheadRussell] p. 100. $)
  imim2 $p |- ( ( ph -> ps ) -> ( ( ch -> ph ) -> ( ch -> ps ) ) ) $=
    wph wps wi wch wph wps wph wps wi wch ax-1 a2d $.
    $( [5-Aug-1993] $)

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.06 of
     [WhiteheadRussell] p. 100. $)
  imim1 $p |- ( ( ph -> ps ) -> ( ( ps -> ch ) -> ( ph -> ch ) ) ) $=
    wps wch wi wph wps wi wph wch wi wps wch wph imim2 com12 $.
    $( [5-Aug-1993] $)

  ${
    imim1i.1 $e |- ( ph -> ps ) $.
    $( Inference adding common consequents in an implication, thereby
       interchanging the original antecedent and consequent. $)
    imim1i $p |- ( ( ps -> ch ) -> ( ph -> ch ) ) $=
      wph wps wi wps wch wi wph wch wi wi imim1i.1 wph wps wch imim1 ax-mp $.
      $( [5-Aug-1993] $)

    $( Inference adding common antecedents in an implication. $)
    imim2i $p |- ( ( ch -> ph ) -> ( ch -> ps ) ) $=
      wch wph wps wph wps wi wch imim1i.1 a1i a2i $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim12i.1 $e |- ( ph -> ps ) $.
    imim12i.2 $e |- ( ch -> th ) $.
    $( Inference joining two implications. $)
    imim12i $p |- ( ( ps -> ch ) -> ( ph -> th ) ) $=
      wps wch wi wps wth wi wph wth wi wch wth wps imim12i.2 imim2i wph wps wth
      imim12i.1 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim3i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference adding three nested antecedents. $)
    imim3i $p |- ( ( th -> ph ) -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wth wph wi wth wps wch wph wps wch wi wth imim3i.1 imim2i a2d $.
      $( [19-Dec-2006] $) $( [19-Dec-2006] $)
  $}

  ${
    3syl.1 $e |- ( ph -> ps ) $.
    3syl.2 $e |- ( ps -> ch ) $.
    3syl.3 $e |- ( ch -> th ) $.
    $( Inference chaining two syllogisms. $)
    3syl $p |- ( ph -> th ) $=
      wph wch wth wph wps wch 3syl.1 3syl.2 syl 3syl.3 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5.2 $e |- ( th -> ps ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the second antecedent of the first premise. $)
    syl5 $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wi wth wch wi syl5.1 wth wps wch syl5.2 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6.2 $e |- ( ch -> th ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl6 $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syl6.1 wch wth wps syl6.2 imim2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl7.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl7.2 $e |- ( ta -> ch ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the third antecedent of the first premise. $)
    syl7 $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wch wth wi wta wth wi syl7.1 wta wch wth syl7.2 imim1i syl6 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl8.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl8.2 $e |- ( th -> ta ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl8 $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syl8.1 wth wta wch syl8.2 imim2i syl6 $.
      $( [1-Aug-1994] $)
  $}

  ${
    imim2d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested antecedents. $)
    imim2d $p |- ( ph -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wph wth wps wch wph wps wch wi wth imim2d.1 a1d a2d $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpd.1 $e |- ( ph -> ps ) $.
    mpd.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A modus ponens deduction. $)
    mpd $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi mpd.1 wph wps wch mpd.2 a2i ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    syld.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syld.2 $e |- ( ph -> ( ch -> th ) ) $.
    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       19-Feb-2008.  See ~ syldOLD for previous version.) $)
    syld $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syld.1 wph wch wth wps syld.2 imim2d mpd $.
      $( [19-Feb-2008] $) $( [5-Aug-1993] $)

    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       7-Aug-2004.) $)
    syldOLD $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wi wph wps wth wi wi syld.1 wph wps wch wi wps wth wi wph
      wch wth wps syld.2 imim2d a2i ax-mp $.
      $( [7-Aug-2004] $) $( [5-Aug-1993] $)
  $}

  ${
    imim1d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested consequents. $)
    imim1d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> th ) ) ) $=
      wph wps wch wi wch wth wi wps wth wi wi imim1d.1 wps wch wth imim1 syl $.
      $( [3-Apr-1994] $)
  $}

  ${
    imim12d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    imim12d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( Deduction combining antecedents and consequents. $)
    imim12d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> ta ) ) ) $=
      wph wch wth wi wps wth wi wps wta wi wph wps wch wth imim12d.1 imim1d wph
      wth wta wps imim12d.2 imim2d syld $.
      $( [7-Aug-1994] $)
  $}

  $( Swap antecedents.  Theorem *2.04 of [WhiteheadRussell] p. 100. $)
  pm2.04 $p |- ( ( ph -> ( ps -> ch ) ) -> ( ps -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wph wps wi wph wch wi wps wph wps wch ax-2 wps wph ax-1
    syl5 $.
    $( [5-Aug-1993] $)

  $( Theorem *2.83 of [WhiteheadRussell] p. 108. $)
  pm2.83 $p |-  ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ( ch -> th ) ) ->
                ( ph -> ( ps -> th ) ) ) ) $=
    wps wch wi wch wth wi wps wth wi wph wps wch wth imim1 imim3i $.
    $( [13-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    com3.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Commutation of antecedents.  Swap 2nd and 3rd. $)
    com23 $p |- ( ph -> ( ch -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wch wps wth wi wi com3.1 wps wch wth pm2.04 syl $.
      $( [5-Aug-1993] $)

    $( Commutation of antecedents.  Swap 1st and 3rd. $)
    com13 $p |- ( ch -> ( ps -> ( ph -> th ) ) ) $=
      wps wch wph wth wi wps wph wch wth wph wps wch wth wi com3.1 com12 com23
      com12 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left. $)
    com3l $p |- ( ps -> ( ch -> ( ph -> th ) ) ) $=
      wph wch wps wth wph wps wch wth com3.1 com23 com13 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com3r $p |- ( ch -> ( ph -> ( ps -> th ) ) ) $=
      wps wch wph wth wph wps wch wth com3.1 com3l com3l $.
      $( [25-Apr-1994] $)
  $}

  ${
    com4.1 $e |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $.
    $( Commutation of antecedents.  Swap 3rd and 4th. $)
    com34 $p |- ( ph -> ( ps -> ( th -> ( ch -> ta ) ) ) ) $=
      wph wps wch wth wta wi wi wth wch wta wi wi com4.1 wch wth wta pm2.04
      syl6 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 2nd and 4th. $)
    com24 $p |- ( ph -> ( th -> ( ch -> ( ps -> ta ) ) ) ) $=
      wph wth wps wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com23 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 1st and 4th. $)
    com14 $p |- ( th -> ( ps -> ( ch -> ( ph -> ta ) ) ) ) $=
      wth wps wph wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com13 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left.  (The proof was shortened by
       Mel L. O'Cat, 15-Aug-2004.) $)
    com4l $p |- ( ps -> ( ch -> ( th -> ( ph -> ta ) ) ) ) $=
      wth wps wch wph wta wi wph wps wch wth wta com4.1 com14 com3l $.
      $( [15-Aug-2004] $) $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate twice. $)
    com4t $p |- ( ch -> ( th -> ( ph -> ( ps -> ta ) ) ) ) $=
      wps wch wth wph wta wph wps wch wth wta com4.1 com4l com4l $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com4r $p |- ( th -> ( ph -> ( ps -> ( ch -> ta ) ) ) ) $=
      wch wth wph wps wta wph wps wch wth wta com4.1 com4t com4l $.
      $( [25-Apr-1994] $)
  $}

  ${
    a1dd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction introducing a nested embedded antecedent.  (The proof was
       shortened by Mel L. O'Cat, 15-Jan-2008.) $)
    a1dd $p |- ( ph -> ( ps -> ( th -> ch ) ) ) $=
      wph wps wch wth wch wi a1dd.1 wch wth ax-1 syl6 $.
      $( [15-Jan-2008] $) $( [17-Dec-2004] $)
  $}

  ${
    mp2.1 $e |- ph $.
    mp2.2 $e |- ps $.
    mp2.3 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A double modus ponens inference. $)
    mp2 $p |- ch $=
      wps wch mp2.2 wph wps wch wi mp2.1 mp2.3 ax-mp ax-mp $.
      $( [5-Apr-1994] $)
  $}

  ${
    mpi.1 $e |- ps $.
    mpi.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A nested modus ponens inference.  (The proof was shortened by Stefan
       Allan, 20-Mar-06. $)
    mpi $p |- ( ph -> ch ) $=
      wph wps wch wps wph mpi.1 a1i mpi.2 mpd $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    mpii.1 $e |- ch $.
    mpii.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A doubly nested modus ponens inference. $)
    mpii $p |- ( ph -> ( ps -> th ) ) $=
      wph wch wps wth wi mpii.1 wph wps wch wth mpii.2 com23 mpi $.
      $( [31-Dec-1993] $)
  $}

  ${
    mpdd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    mpdd.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpdd $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi mpdd.1 wph wps wch wth mpdd.2 a2d mpd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpid.1 $e |- ( ph -> ch ) $.
    mpid.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpid $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wch wps mpid.1 a1d mpid.2 mpdd $.
      $( [16-Dec-2004] $) $( [14-Dec-2004] $)
  $}

  ${
    mpdi.1 $e |- ( ps -> ch ) $.
    mpdi.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction.  (The proof was shortened by Mel L.
       O'Cat, 15-Jan-2008.) $)
    mpdi $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wps wch wi wph mpdi.1 a1i mpdi.2 mpdd $.
      $( [15-Jan-2008] $) $( [16-Apr-2005] $)
  $}

  ${
    mpcom.1 $e |- ( ps -> ph ) $.
    mpcom.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus ponens inference with commutation of antecedents. $)
    mpcom $p |- ( ps -> ch ) $=
      wps wph wch mpcom.1 wph wps wch mpcom.2 com12 mpd $.
      $( [17-Mar-1996] $)
  $}

  ${
    syldd.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syldd.2 $e |- ( ph -> ( ps -> ( th -> ta ) ) ) $.
    $( Nested syllogism deduction. $)
    syldd $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syldd.1 wph wps wth wta wi wch wth wi wch
      wta wi wi syldd.2 wth wta wch imim2 syl6 mpdd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

