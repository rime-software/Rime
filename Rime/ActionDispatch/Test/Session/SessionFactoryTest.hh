<?hh // strict

namespace Rime\ActionDispatch\Test;
use Rime\ActionDispatch\Session\Factory\SessionFactory as SessionFactory;

class SessionFactoryTest extends \PHPUnit_Framework_TestCase
{
    public function testNewInstance()
    {
        $session_factory = new SessionFactory;
        $session = $session_factory->newInstance($_COOKIE);
        $this->assertInstanceOf('Rime\ActionDispatch\Session\User\Session', $session);
    }
}