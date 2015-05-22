<?hh // strict

namespace Rime\ActionDispatch\Session\Implementation;

interface RandvalInterface
{
  public function generate(): ?string;
}
