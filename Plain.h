#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Agent/PLAAGTScene.hpp"
#include "Agent/PLAAGTState.hpp"
#include "Agent/PLAAGTModel.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"

#include "Core/PLARendererType.hpp"
#include "Core/PLAFunctionCode.hpp"

class Plain {
public:
  using Renderer = PLARendererType;

  static void Init(PLARendererType aType);
  static void Delete(const std::string &aName);

  static void Add(const PLAAGTActor &aActor);
  static void Add(const PLAAGTModel &aModel);

  static void Push(const PLAAGTScene &aAgent);

  class Event {
  public:
    using Actor = PLAFunctionCode::Actor;
    using Stage = PLAFunctionCode::Stage;
    using Scene = PLAFunctionCode::Scene;

    /// Delete copy and move constructors and assign operators
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) = delete;
    Event& operator=(Event&&) = delete;

  private:
    /// Delete default constructor and destructor
    Event() = delete;
    ~Event() = delete;
  };

  class Error {
  public:
    using Type = PLAErrorType;
    static void Assert(const std::string &aMessage);
    static void Expect(const std::string &aMessage);

    /// Delete copy and move constructors and assign operators
    Error(const Error&) = delete;
    Error& operator=(const Error&) = delete;
    Error(Error&&) = delete;
    Error& operator=(Error&&) = delete;

  private:
    /// Delete default constructor and destructor
    Error() = delete;
    ~Error() = delete;
  };

  class Print {
  public:
    static void Objects();
    static void Resources();

    /// Delete copy and move constructors and assign operators
    Print(const Print&) = delete;
    Print& operator=(const Print&) = delete;
    Print(Print&&) = delete;
    Print& operator=(Print&&) = delete;

  private:
    /// Delete default constructor and destructor
    Print() = delete;
    ~Print() = delete;
  };

  class State {
  public:
    static PLAAGTState Assign();

    /// Delete copy and move constructors and assign operators
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

  private:
    /// Delete default constructor and destructor
    State() = delete;
    ~State() = delete;
  };

  class Stage {
  public:
    static PLAAGTStage Assign();
    static void SetFunction(Event::Stage aEventCode);

    /// Delete copy and move constructors and assign operators
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;
    Stage(Stage&&) = delete;
    Stage& operator=(Stage&&) = delete;

  private:
    /// Delete default constructor and destructor
    Stage() = delete;
    ~Stage() = delete;
  };

  class Scene {
  public:
    static PLAAGTScene Create();
    static PLAAGTScene Create(const PLAString &aName);
    static PLAAGTScene Assign(const PLAString &aName);

    /// Delete copy and move constructors and assign operators
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&&) = delete;

  private:
    /// Delete default constructor and destructor
    Scene() = delete;
    ~Scene() = delete;
  };

  class Model {
  public:
    static PLAAGTModel Create();
    static PLAAGTModel Create(const PLAString &aName);
    static PLAAGTModel Assign(const PLAString &aName);

    /// Delete copy and move constructors and assign operators
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&&) = delete;

  private:
    /// Delete default constructor and destructor
    Model() = delete;
    ~Model() = delete;
  };

  class Actor {
  public:
    static PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                                  const PLAColor &aColor,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect);
    static PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                                  const PLAColor &aColor,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const PLAColor &aFillColor);
    static PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                                  const PLAColor &aColor,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const std::string &aImage,
                                  const PLARect &aClip);
    static PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                                    const PLAColor &aColor,
                                    const PLATransform &aTransform,
                                    const PLACircle &aCircle);
    static PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                                    const PLAColor &aColor,
                                    const PLATransform &aTransform,
                                    const PLACircle &aCircle,
                                    const PLAColor &aFillColor);
    static PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                                    const PLAColor &aColor,
                                    const PLATransform &aTransform,
                                    const PLACircle &aCircle,
                                    const std::string &aImage,
                                    const PLARect &aClip);
    static PLAAGTActor CreateTile(const PLAVec2f &aOffset,
                                  const std::string &aImageName,
                                  const GRAVec2<PLASize> &aTileSize,
                                  const GRAVec2<PLASize> &aChipSize,
                                  const IPLATileLayerDataSource *aDataSource);
    static PLAAGTActor Assign(const PLAString &aName);

    /// Delete copy and move constructors and assign operators
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;
    Actor(Plain&&) = delete;
    Actor& operator=(Actor&&) = delete;

  private:
    /// Delete default constructor and destructor
    Actor() = delete;
    ~Actor() = delete;
  };

  /// Delete copy and move constructors and assign operators
  Plain(const Plain&) = delete;
  Plain& operator=(const Plain&) = delete;
  Plain(Plain&&) = delete;
  Plain& operator=(Plain&&) = delete;

private:
  /// Delete default constructor and destructor
  Plain() = delete;
  ~Plain() = delete;
};

#endif //PLAIN_ENGINE_PLAIN_HPP
