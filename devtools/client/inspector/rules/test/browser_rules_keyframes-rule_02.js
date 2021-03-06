/* Any copyright is dedicated to the Public Domain.
 http://creativecommons.org/publicdomain/zero/1.0/ */

"use strict";

// Test that verifies the content of the keyframes rule and property changes
// to keyframe rules.

const TEST_URI = URL_ROOT + "doc_keyframeanimation.html";

add_task(function* () {
  yield addTab(TEST_URI);
  let {inspector, view} = yield openRuleView();
  yield testPacman(inspector, view);
  yield testBoxy(inspector, view);
});

function* testPacman(inspector, view) {
  info("Test content in the keyframes rule of #pacman");

  let rules = yield getKeyframeRules("#pacman", inspector, view);

  info("Test text properties for Keyframes #pacman");

  is(convertTextPropsToString(rules.keyframeRules[0].textProps),
    "left: 750px",
    "Keyframe pacman (100%) property is correct"
  );

  // Dynamic changes test disabled because of Bug 1050940
  // If this part of the test is ever enabled again, it should be changed to
  // use addProperty (in head.js) and stop using _applyingModifications

  // info("Test dynamic changes to keyframe rule for #pacman");

  // let defaultView = element.ownerDocument.defaultView;
  // let ruleEditor = view.element.children[5].childNodes[0]._ruleEditor;
  // ruleEditor.addProperty("opacity", "0", true);

  // yield ruleEditor._applyingModifications;
  // yield once(element, "animationend");

  // is
  // (
  //   convertTextPropsToString(rules.keyframeRules[1].textProps),
  //   "left: 750px; opacity: 0",
  //   "Keyframe pacman (100%) property is correct"
  // );

  // is(defaultView.getComputedStyle(element).getPropertyValue("opacity"), "0",
  //   "Added opacity property should have been used.");
}

function* testBoxy(inspector, view) {
  info("Test content in the keyframes rule of #boxy");

  let rules = yield getKeyframeRules("#boxy", inspector, view);

  info("Test text properties for Keyframes #boxy");

  is(convertTextPropsToString(rules.keyframeRules[0].textProps),
    "background-color: blue",
    "Keyframe boxy (10%) property is correct"
  );

  is(convertTextPropsToString(rules.keyframeRules[1].textProps),
    "background-color: green",
    "Keyframe boxy (20%) property is correct"
  );

  is(convertTextPropsToString(rules.keyframeRules[2].textProps),
    "opacity: 0",
    "Keyframe boxy (100%) property is correct"
  );
}

function convertTextPropsToString(textProps) {
  return textProps.map(t => t.name + ": " + t.value).join("; ");
}

function* getKeyframeRules(selector, inspector, view) {
  yield selectNode(selector, inspector);
  let elementStyle = view._elementStyle;

  let rules = {
    elementRules: elementStyle.rules.filter(rule => !rule.keyframes),
    keyframeRules: elementStyle.rules.filter(rule => rule.keyframes)
  };

  return rules;
}
