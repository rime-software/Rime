<?hh // strict

namespace Rime\ActionDispatch\Session\Factory;

class SegmentFactory
{
  public function newInstance(\Rime\ActionDispatch\Session\User\Session $session, ?string $name): \Rime\ActionDispatch\Session\Segment\Segment
  {
    return new \Rime\ActionDispatch\Session\Segment\Segment($session, $name);
  }
}
