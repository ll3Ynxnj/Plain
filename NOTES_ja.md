# Now
Timeline関連のAgentを実装した。

# Tasks
- Phaseの切り替えにStageとModelをシームレスに連動させたい。
- StageとStateは、Phase切替を検知するListenerをSceneに登録する。

# Tasks(Completed)
- Sceneの子属性としてPhaseを実装する。

# Memo
Phaseの切り替えをStageとModelに検知させる。

# ライフサイクルについて
1. 入力の受け取り
2. Stageの更新

# ファンクタの実行について

# Agentについて
Agentは、Objectの代理人です。ユーザーはAgentを通してObjectを操作します。Agentはconstメソッドしか持ちません。AgentをAssignした場合、ポインタではなく実態が生成され、スコープ外に出ると破棄されます。
