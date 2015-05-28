<?hh // strict

namespace Rime\System\Performance;

final class MicroTimer
{
  private Map<int> $timers = Map{};
  
  public function addTimer(string $alias, boolean $float = true): void
  {
    $this->timers[$alias] = microtime($float);
  }
  
  public function getExecutionTime(string $alias, boolean $float = true): mixed
  {
    if($this->timers->contains($alias))
      return microtime($float) - $this->timers->get($alias);
    else
      return 0;
  }
  
  public function printMessage(string $regexString, string $alias, boolean $float = true): void
  {
    if($this->timers->contains($alias))
      printf($regexString, $this->getExecutionTime($alias,$float));
    else
      printf($regexString,0);
  }
  
}