#pragma once

#include <memory>

class PrintConcept final {
 public:
  template <typename Object>
  PrintConcept(Object object)
      : inner_concept_bridge_(
            std::make_unique<InnerConceptAdapter<Object>>(object)) {}

  void print() const { inner_concept_bridge_->print(); }

 private:
  struct InnerConcept {
    virtual ~InnerConcept() = default;
    virtual void print() const = 0;
  };
  template <typename Type>
  struct InnerConceptAdapter final : InnerConcept {
    InnerConceptAdapter(Type object) : this_(object) {}
    void print() const override { this_.print(); }
    Type this_;
  };

  std::unique_ptr<InnerConcept> inner_concept_bridge_;
};
