# Now
Timeline関連のAgentを実装した。
AgentからOwnerへのアクセサをpublicにしたコミットは取り消す。オーナーへのアクセスはIDからの間接参照で実現する方針。

# Tasks
- Phaseの切り替えにStageとModelをシームレスに連動させたい。
- StageとStateは、Phase切替を検知するListenerをSceneに登録する。

# Tasks(Completed)
- Sceneの子属性としてPhaseを実装する。

# Memo
Phaseの切り替えをStageとModelに検知させる。
ActorのOnAppear, OnDisappearを利用して、画面を遷移させる感じかな。
すべてのObjectに名前付きのCreateメソッド、Create(PLAString aName)を追加する。
ActorのBinderをPLAOBJActorにしているが、Binderの用途は、たぶん階層に関わらず一意のIDで検索ができることなので、PLAOBJStageをBinderにするほうが適切なのでは？ただ、現状検討中なので、PhaseのBinderも同じ考え方でSceneではなくPhaseにしてみる。
バインダーは全てPLAId型を持つようにしたら良いんでない？
Timelineの破棄に不備がある気がする。コンソールに不正な値を出力するOnStop関数が実行されているので。（例: : Timeline::OnStop(), _steps: 25021713）

# OnInitの廃止について
OnInitは初期化を行うためのファンクタだが、初期化は実行されるタイミングがオブジェクト生成後一度きりのため、オブジェクト生成後にAddFunctor関数を使って登録しても、実行されない可能性が高い。ファンクタとして実装するのは不適切。CREATEメソッドに関数オブジェクトを含めるのが良いかも。

# オブジェクトの参照方法について
Actor、Phaseの子オブジェクトへの参照に、ポインタを使用しているが、PLAIdのほうが良い気がする。

# オブジェクトの生成と削除について
ユーザーが明示的に作成したオブジェクトのみがバインダーに追加されるようにするべき。オブジェクト内で自動生成される子オブジェクトは、Createファクトリメソッドかコンストラクタで生成され、削除はいずれもデストラクタで行う。ファクトリメソッドの対応メソッドを作ろうなどとは思わないことだ。

# ライフサイクルについて
1. 入力の受け取り
2. Stageの更新

# ファンクタの実行について

# Agentについて
Agentは、Objectの代理人です。ユーザーはAgentを通してObjectを操作します。Agentはconstメソッドしか持ちません。AgentをAssignした場合、ポインタではなく実態が生成され、スコープ外に出ると破棄されます。Agentの実態は、オブジェクトへの参照のみなので、参照を利用する機会は多分ありません。

# Motionの持ち主（?）について
すでにどこかに追加されているMotionを別の場所に追加した場合、何が起きるのかは検証しておく必要がある
