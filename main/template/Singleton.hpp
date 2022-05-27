#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

/// <summary>
/// �ν��Ͻ� Ÿ�Կ� ���� �̱���
/// </summary>
/// <typeparam name="INSTANCE_TYPE">�ν��Ͻ� Ÿ��</typeparam>
template <typename INSTANCE_TYPE>
class SINGLETON
{
public:
	/// <summary>
	/// �ڽ��� ���� �ν��Ͻ� ���� ��ȯ
	/// </summary>
	/// <returns>�ڽ��� ���� �ν��Ͻ� ����</returns>
	static INSTANCE_TYPE& GetInstance()
	{
		if (_instance == NULL)
			_instance = new INSTANCE_TYPE();

		return *_instance;
	}

	/// <summary>
	/// �ڽ��� ���� �ν��Ͻ� �޸� �Ҵ� ����
	/// </summary>
	static void Dispose()
	{
		delete _instance;
		_instance = NULL;
	}

protected:
	static INSTANCE_TYPE* _instance; //���� �ν��Ͻ�
};

template<typename INSTANCE_TYPE>
INSTANCE_TYPE* SINGLETON<INSTANCE_TYPE>::_instance = NULL;
#endif