#include <core/classifier.h>
#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize), static_cast<int>(kWindowSize));
}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();

  ci::gl::drawStringCentered(
      "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Prediction: " + std::to_string(current_prediction_),
      glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"));
}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN: {
      naivebayes::Model model(kImageDimension);
      std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/model.txt";
      std::ifstream load_file(file);
      load_file >> model;
      
      naivebayes::Classifier classifier(model);
      current_prediction_ =
          classifier.CalculateLikelihoodScores(sketchpad_.GetImage());
      break;
    }

    case ci::app::KeyEvent::KEY_DELETE:
      sketchpad_.Clear();
      current_prediction_ = -1;
      break;
      
  }
}

}  // namespace visualizer

}  // namespace naivebayes
